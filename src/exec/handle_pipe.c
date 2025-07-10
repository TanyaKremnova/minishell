/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:13:28 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 12:39:12 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_ast *ast, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), shell->last_exit_status = 1, 1);
	signal(SIGINT, SIG_IGN);
	pid1 = child_left(ast->left, pipefd, shell);
	if (pid1 == -1)
		return (handle_pipe_error(pipefd, -1, shell));
	pid2 = child_right(ast->right, pipefd, shell);
	if (pid2 == -1)
		return (handle_pipe_error(pipefd, pid1, shell));
	close_exit(pipefd, 0);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	handle_signal_message(status);
	set_exit_status_waitpid(status, shell);
	setup_signals();
	return (0);
}

pid_t	child_left(t_ast *left, int pipefd[2], t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork (left)");
		return (-1);
	}
	if (pid == 0)
	{
		rl_clear_history();
		setup_child_signals();
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 (left)");
			close_exit(pipefd, 1);
		}
		close_exit(pipefd, 0);
		execute_ast(left, shell);
		free_env(shell->env);
		free_ast(&shell->ast);
		exit(shell->last_exit_status);
	}
	return (pid);
}

pid_t	child_right(t_ast *right, int pipefd[2], t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork (right)");
		return (-1);
	}
	if (pid == 0)
	{
		rl_clear_history();
		setup_child_signals();
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 (right)");
			close_exit(pipefd, 1);
		}
		close_exit(pipefd, 0);
		execute_ast(right, shell);
		free_env(shell->env);
		free_ast(&shell->ast);
		exit(shell->last_exit_status);
	}
	return (pid);
}

int	handle_pipe_error(int *pipefd, pid_t pid1, t_shell *shell)
{
	close_exit(pipefd, 0);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	shell->last_exit_status = 1;
	return (1);
}

void	close_exit(int pipefd[2], int should_exit)
{
	if (pipefd[0] > 2)
		close(pipefd[0]);
	if (pipefd[1] > 2)
		close(pipefd[1]);
	if (should_exit)
		exit(1);
}
