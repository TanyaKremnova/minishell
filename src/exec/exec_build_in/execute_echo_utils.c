/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:48:07 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 11:29:25 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (false);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	count_exit_vars(const char *arg)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = (char *)arg;
	tmp = ft_strnstr(tmp, "$?", ft_strlen(tmp));
	while (tmp)
	{
		count++;
		tmp += 2;
		tmp = ft_strnstr(tmp, "$?", ft_strlen(tmp));
	}
	return (count);
}

void	append_char(char *result, const char *tmp)
{
	size_t	len;

	len = 0;
	len = ft_strlen(result);
	result[len] = *tmp;
	result[len + 1] = '\0';
}
