/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd_util.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tkremnov <tkremnov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 17:09:34 by tkremnov      #+#    #+#                 */
/*   Updated: 2025/07/02 13:50:42 by lperekhr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_new_pwd(char *newpwd, t_shell *shell)
{
	char	*fallback;

	if (getcwd(newpwd, SHELL_PATH_MAX))
		update_env_var(shell, "PWD", newpwd);
	else
	{
		fallback = get_env_value(shell->env, "PWD");
		if (fallback)
			update_env_var(shell, "PWD", fallback);
		else
			perror("minishell: cd: getcwd (after)");
	}
}

char	**add_to_env(char **env, const char *new_var)
{
	int		len;
	char	**new_env;
	int		i;

	len = 0;
	while (env && env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (ft_free_from_the_end(new_env, i));
		i++;
	}
	new_env[len] = ft_strdup(new_var);
	if (!new_env[len])
		return (ft_free_from_the_end(new_env, i));
	new_env[len + 1] = NULL;
	free_env(env);
	return (new_env);
}

void	update_env_var(t_shell *shell, const char *key, const char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	key_len = ft_strlen(key);
	new_var = ft_strjoin3(key, "=", value);
	if (!new_var)
		return ;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_var;
			return ;
		}
		i++;
	}
	shell->env = add_to_env(shell->env, new_var);
	free(new_var);
}
