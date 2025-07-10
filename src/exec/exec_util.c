/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:58:00 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/27 15:04:34 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status_waitpid(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	else
		shell->last_exit_status = 1;
}

int	save_std_fds(t_shell *shell)
{
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
	{
		perror("dup STDOUT");
		return (1);
	}
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
	{
		perror("dup STDIN");
		close(shell->saved_stdout);
		return (1);
	}
	return (0);
}

void	restore_std_fds(t_shell *shell)
{
	if (shell->saved_stdout != -1)
	{
		if (dup2(shell->saved_stdout, STDOUT_FILENO) == -1)
			perror("restore STDOUT");
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
	if (shell->saved_stdin != -1)
	{
		if (dup2(shell->saved_stdin, STDIN_FILENO) == -1)
			perror("restore STDIN");
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
}
