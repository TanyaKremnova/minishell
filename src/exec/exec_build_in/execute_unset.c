/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:29:18 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/27 16:54:04 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(char **args, t_shell *shell)
{
	int	i;

	shell->last_exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->last_exit_status = 1;
			i++;
			continue ;
		}
		remove_env_var(&(shell->env), args[i]);
		i++;
	}
}

void	remove_env_var(char ***env, const char *key)
{
	int		i;
	int		j;
	size_t	key_len;
	char	**new_env;

	key_len = ft_strlen(key);
	i = env_len(*env);
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if ((ft_strncmp((*env)[i], key, key_len) == 0)
			&& ((*env)[i][key_len] == '=' || (*env)[i][key_len] == '\0'))
			free((*env)[i]);
		else
			new_env[j++] = (*env)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
}
