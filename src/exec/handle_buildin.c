/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buildin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:58:11 by lperekhr          #+#    #+#             */
/*   Updated: 2025/07/01 10:09:19 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

void	handle_buildin(t_ast *ast, t_shell *shell)
{
	char	**args;

	if (!ast || !ast->args)
		return ;
	if (ft_strcmp(ast->args->value, "echo") == 0)
		execute_echo(ast->args->next, shell);
	else
	{
		args = build_cmd(ast->args);
		if (!args)
			return ;
		if (ft_strcmp(args[0], "export") == 0)
			execute_export(args, shell);
		else if (ft_strcmp(args[0], "unset") == 0)
			execute_unset(args, shell);
		else if (ft_strcmp(args[0], "env") == 0)
			execute_env(shell);
		else if (ft_strcmp(args[0], "cd") == 0)
			execute_cd(args, shell);
		else if (ft_strcmp(args[0], "pwd") == 0)
			execute_pwd(shell);
		else if (ft_strcmp(args[0], "exit") == 0)
			execute_exit(args, shell);
		free_array(args);
	}
}
