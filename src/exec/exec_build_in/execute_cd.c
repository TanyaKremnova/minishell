/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:26:39 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 11:27:57 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(char **args, t_shell *shell)
{
	char	oldpwd[SHELL_PATH_MAX];
	char	newpwd[SHELL_PATH_MAX];
	char	*target;

	target = get_cd_target(args, shell);
	if (!target)
		return ;
	if (!get_current_or_env_pwd(oldpwd, shell))
		return ;
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		shell->last_exit_status = 1;
		return ;
	}
	update_env_var(shell, "OLDPWD", oldpwd);
	update_new_pwd(newpwd, shell);
	shell->last_exit_status = 0;
}

char	*get_cd_target(char **args, t_shell *shell)
{
	char	*target;

	if (!args[1])
	{
		ft_putstr_fd("minishell: cd: missing argument\n", 2);
		shell->last_exit_status = 1;
		return (NULL);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value(shell->env, "OLDPWD");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			shell->last_exit_status = 1;
			return (NULL);
		}
		ft_putendl_fd(target, 1);
	}
	else
		target = args[1];
	return (target);
}

int	get_current_or_env_pwd(char *buffer, t_shell *shell)
{
	char	*env_pwd;

	if (getcwd(buffer, SHELL_PATH_MAX))
		return (1);
	env_pwd = get_env_value(shell->env, "PWD");
	if (env_pwd)
	{
		ft_strlcpy(buffer, env_pwd, SHELL_PATH_MAX);
		return (1);
	}
	perror("minishell: cd: getcwd (before)");
	shell->last_exit_status = 1;
	return (0);
}
