/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:58:31 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 11:12:06 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(char *result, int last_exit_status)
{
	char	*status_str;
	char	*tmp;

	status_str = ft_itoa(last_exit_status);
	if (!status_str)
	{
		free(result);
		return (NULL);
	}
	tmp = ft_strjoin_free(result, status_str);
	free(status_str);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*expand_normal_variable(const char *str, int *i, t_shell *shell,
			char *result)
{
	char	var_name[EXEC_PATH_MAX];
	char	*val;
	char	*tmp;

	*i = read_var_name(str, *i, var_name);
	if (var_name[0])
	{
		val = get_env_value(shell->env, var_name);
		if (val)
			tmp = ft_strjoin_free(result, val);
		else
			tmp = ft_strjoin_free(result, "");
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	else
	{
		tmp = ft_strjoin_char_free(result, '$');
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	return (result);
}

char	*ft_strjoin_char_free(char *s, char c)
{
	char	*new;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(len + 2);
	if (!new)
	{
		free(s);
		return (NULL);
	}
	ft_memcpy(new, s, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

int	read_var_name(const char *str, int i, char *var_name)
{
	int	j;

	j = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		var_name[j++] = str[i++];
	var_name[j] = '\0';
	return (i);
}

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
