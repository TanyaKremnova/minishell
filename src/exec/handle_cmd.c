/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:49:48 by lperekhr          #+#    #+#             */
/*   Updated: 2025/07/02 12:41:21 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_cmd(t_arg *args)
{
	char	**cmd_arguments;
	t_arg	*curr;
	int		args_count;
	int		i;

	curr = args;
	args_count = count_args(curr);
	i = 0;
	cmd_arguments = malloc(sizeof(char *) * (args_count + 1));
	if (!cmd_arguments)
		return (NULL);
	curr = args;
	while (i < args_count)
	{
		cmd_arguments[i] = ft_strdup(curr->value);
		if (!cmd_arguments[i])
		{
			free_array(cmd_arguments);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	cmd_arguments[args_count] = NULL;
	return (cmd_arguments);
}

void	handle_command(t_ast *ast, t_shell *shell)
{
	t_exec_cmd	cmd;
	pid_t		pid;

	if (!ast->args->value || ast->args->value[0] == '\0')
	{
		ft_putstr_fd("minishell: command '' not found\n", STDERR_FILENO);
		shell->last_exit_status = 127;
		return ;
	}
	if (!prepare_command_and_path(&cmd, ast, shell))
		return ;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	handle_fork_result(pid, ast, shell, &cmd);
	setup_signals();
}

bool	prepare_command_and_path(t_exec_cmd *cmd, t_ast *ast, t_shell *shell)
{
	char	err[SHELL_PATH_MAX];

	if (ft_strchr(ast->args->value, '/'))
		cmd->path = ft_strdup(ast->args->value);
	else
		cmd->path = find_command_path(ast->args->value, shell->env);
	if (!cmd->path)
	{
		short_command(err, sizeof(err), ast->args->value);
		ft_putstr_fd(err, STDERR_FILENO);
		shell->last_exit_status = 127;
		return (false);
	}
	cmd->cmd = build_cmd(ast->args);
	if (!cmd->cmd)
	{
		ft_putstr_fd("minishell: error: failed to build command\n",
			STDERR_FILENO);
		shell->last_exit_status = 1;
		free(cmd->path);
		cmd->path = NULL;
		return (false);
	}
	return (true);
}

void	handle_fork_result(pid_t pid, t_ast *ast,
			t_shell *shell, t_exec_cmd *cmd)
{
	int	status;

	if (pid < 0)
	{
		perror("fork");
		shell->last_exit_status = 1;
	}
	else if (pid == 0)
		handle_child_process(ast, shell, cmd);
	else
	{
		waitpid(pid, &status, 0);
		handle_signal_message(status);
		set_exit_status_waitpid(status, shell);
	}
	free_cmd_and_path(cmd->cmd, cmd->path);
}

void	handle_child_process(t_ast *ast, t_shell *shell, t_exec_cmd *cmd)
{
	int	err;

	rl_clear_history();
	setup_child_signals();
	if (handle_redirections(ast->redirections, shell) != 0)
	{
		rl_clear_history();
		exit(1);
	}
	err = check_command_access(cmd->path);
	if (err == 126)
		print_permission_error(cmd->path, cmd, shell);
	if (execve(cmd->path, cmd->cmd, shell->env) == -1)
	{
		perror("minishell");
		free_cmd_and_path(cmd->cmd, cmd->path);
		free_ast(&shell->ast);
		free_env(shell->env);
		exit(127);
	}
}
