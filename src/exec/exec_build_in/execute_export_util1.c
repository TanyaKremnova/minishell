/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_util1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:53 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/27 16:50:50 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	if (str[0] == '=' || (str[0] == '+' && str[1] == '='))
		return (false);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	has_plus_equal(const char *str)
{
	const char	*equal;

	equal = ft_strchr(str, '=');
	if (equal && equal > str && *(equal - 1) == '+')
		return (true);
	return (false);
}

void	sort_env_array(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	if (!env)
		return ;
	len = env_len(env);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

bool	is_append_var(const char *var)
{
	while (*var && *(var + 1))
	{
		if (*var == '+' && *(var + 1) == '=')
			return (true);
		var++;
	}
	return (false);
}
