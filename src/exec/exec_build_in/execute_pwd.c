/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:25:16 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/26 13:49:20 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(t_shell *shell)
{
	char	cwd[SHELL_PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		pwd = get_env_value(shell->env, "PWD");
		if (pwd)
			ft_putendl_fd(pwd, 1);
		else
		{
			perror("pwd");
			shell->last_exit_status = 1;
			return ;
		}
	}
	else
		ft_putendl_fd(cwd, 1);
	shell->last_exit_status = 0;
}
