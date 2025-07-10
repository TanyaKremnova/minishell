/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:51:24 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/26 18:02:07 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

bool	is_operator(char c)
{
	return ((c == '|') || (c == '\'') || (c == '\"')
		|| (c == '>') || (c == '<'));
}

bool	is_glued(const char *str, int prev_end, int curr_start)
{
	int	i;

	if (prev_end < 0 || prev_end > curr_start)
		return (false);
	i = prev_end;
	while (i < curr_start)
	{
		if (is_space(str[i]))
			return (false);
		i++;
	}
	return (true);
}
