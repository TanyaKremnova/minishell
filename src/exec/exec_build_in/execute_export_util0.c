/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_util0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:39:59 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/27 16:13:21 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_list(char **env)
{
	char	**copy;
	int		i;
	char	*equal;
	int		key_len;

	copy = copy_env(env);
	if (!copy)
		return ;
	sort_env_array(copy);
	i = 0;
	while (copy[i])
	{
		equal = ft_strchr(copy[i], '=');
		if (equal)
		{
			key_len = equal - copy[i];
			printf("declare -x %.*s=\"%s\"\n", key_len, copy[i], equal + 1);
		}
		else
			printf("declare -x %s\n", copy[i]);
		i++;
	}
	free_array(copy);
}

size_t	get_key_length(const char *var, bool is_append)
{
	char	*equal_sign;
	char	*plus_equal;

	equal_sign = ft_strchr(var, '=');
	plus_equal = ft_strnstr(var, "+=", ft_strlen(var));
	if (is_append)
		return (plus_equal - var);
	else if (equal_sign)
		return (equal_sign - var);
	return (ft_strlen(var));
}

char	**copy_env_add(char **env, const char *new_var)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_array(new_env), NULL);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (free_array(new_env), NULL);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	add_update_env(char ***env, const char *var)
{
	size_t	key_len;
	bool	is_append;
	char	**new_env;

	is_append = is_append_var(var);
	key_len = get_key_length(var, is_append);
	if (update_existing_env(env, var, key_len, is_append))
		return ;
	new_env = copy_env_add(*env, var);
	free_array(*env);
	*env = new_env;
}
