/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:54:36 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/27 12:18:16 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*quotes_token(char *str, int *i, int prev_i, const char *full_str)
{
	t_token			*quotes_token;
	char			*word;
	bool			glued;
	t_token_flags	flags;
	char			quote;

	quote = str[*i];
	glued = is_glued(full_str, prev_i, *i);
	quotes_token = NULL;
	word = find_quotes(str, i);
	if (!word)
	{
		ft_putstr_fd("syntax error: unclosed quotes\n", 1);
		return (NULL);
	}
	flags = (t_token_flags){.quoted = true, .glued = glued};
	if (quote == '"')
		quotes_token = create_token(word, TOKEN_DOUBLE_QUOTES, QUOTE_DOUBLE,
				flags);
	else if (quote == '\'')
		quotes_token = create_token(word, TOKEN_SINGLE_QUOTES, QUOTE_SINGLE,
				flags);
	free(word);
	return (quotes_token);
}

char	*find_quotes(char *str, int *i)
{
	char	*word;
	int		a;
	int		end;
	int		start;
	char	quote;

	a = 0;
	quote = str[*i];
	start = ++(*i);
	end = start;
	while (str[*i] && str[*i] != quote)
	{
		(*i)++;
		end++;
	}
	if (str[*i] != quote)
		return (NULL);
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[a++] = str[start++];
	word[a] = '\0';
	(*i)++;
	return (word);
}
