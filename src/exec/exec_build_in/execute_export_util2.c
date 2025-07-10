/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_util2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:25:02 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 13:21:23 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	replace_env_value(char **env_entry, const char *var)
{
	char	*dup;

	dup = ft_strdup(var);
	if (!dup)
		return (false);
	free(*env_entry);
	*env_entry = dup;
	return (true);
}

char	*get_old_env_value(const char *entry)
{
	char	*equal;

	equal = ft_strchr(entry, '=');
	if (equal)
		return (ft_strdup(equal + 1));
	return (ft_strdup(""));
}

char	*join_env_pieces(const char *old, const char *append)
{
	char	*joined;
	char	*new_value;

	joined = ft_strjoin(old, append);
	if (!joined)
		return (NULL);
	new_value = ft_strjoin("=", joined);
	free(joined);
	if (!new_value)
		return (NULL);
	return (new_value);
}

bool	append_env_value(char **env_entry, const char *var, size_t key_len)
{
	char	*name;
	char	*append_value;
	char	*old_value;
	char	*new_value;
	char	*joined;

	name = ft_strndup(var, key_len);
	append_value = ft_strdup(var + key_len + 2);
	if (!name || !append_value)
		return (free(name), free(append_value), false);
	old_value = get_old_env_value(*env_entry);
	if (!old_value)
		return (free(name), free(append_value), false);
	new_value = join_env_pieces(old_value, append_value);
	free(old_value);
	free(append_value);
	if (!new_value)
		return (free(name), false);
	free(*env_entry);
	joined = ft_strjoin_free(name, new_value);
	free(new_value);
	if (!joined)
		return (false);
	*env_entry = joined;
	return (true);
}

bool	update_existing_env(char ***env, const char *var, size_t key_len,
			bool is_append)
{
	int		i;
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, key_len) == 0
		&& ((*env)[i][key_len] == '=' || (*env)[i][key_len] == '\0'))
		{
			if (equal_sign)
			{
				if (is_append)
				{
					if (!append_env_value(&(*env)[i], var, key_len))
						return (false);
				}
				else if (!replace_env_value(&(*env)[i], var))
					return (false);
			}
			return (true);
		}
		i++;
	}
	return (false);
}
