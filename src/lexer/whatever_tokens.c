/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:28:43 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 13:29:05 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*dollar_token(char *str, int *i, int prev_i, const char *full_str)
{
	t_token			*new_token;
	bool			glued;
	t_token_flags	flags;

	glued = is_glued(full_str, prev_i, *i);
	if (str[*i + 1] == '?')
	{
		flags = (t_token_flags){.quoted = false, .glued = glued};
		new_token = create_token("$?", TOKEN_EXIT_STATUS, QUOTE_NONE, flags);
		*i += 2;
	}
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
		new_token = env_variable_token(i, prev_i, full_str);
	else
	{
		flags = (t_token_flags){.quoted = false, .glued = glued};
		new_token = create_token("$", TOKEN_WORD, QUOTE_NONE, flags);
		(*i)++;
	}
	return (new_token);
}

t_token	*env_variable_token(int *i, int prev_i, const char *full_str)
{
	t_token			*token;
	char			*word;
	int				start;
	bool			glued;
	t_token_flags	flags;

	start = *i;
	glued = is_glued(full_str, prev_i, *i);
	(*i)++;
	while (full_str[*i] && (ft_isalnum(full_str[*i]) || full_str[*i] == '_'))
		(*i)++;
	word = ft_substr(full_str, start, *i - start);
	if (!word)
		return (NULL);
	flags = (t_token_flags){.quoted = false, .glued = glued};
	token = create_token(word, TOKEN_ENV_VARIABLE, QUOTE_NONE, flags);
	free(word);
	return (token);
}

t_token	*pipe_token(char *str, int *i)
{
	t_token			*pipe_token;
	char			word[2];
	t_token_flags	flags;

	if (str[*i] == '|')
		word[0] = str[(*i)++];
	word[1] = '\0';
	flags = (t_token_flags){.quoted = false, .glued = false};
	pipe_token = create_token(word, TOKEN_PIPE, QUOTE_NONE, flags);
	return (pipe_token);
}

t_token	*word_token(char *str, int *i, int prev_i, const char *full_str)
{
	t_token			*word_token;
	char			*word;
	int				a;
	bool			glued;
	t_token_flags	flags;

	glued = is_glued(full_str, prev_i, *i);
	flags = (t_token_flags){.quoted = false, .glued = glued};
	a = 0;
	word = malloc(ft_strlen(str) + 1);
	if (!word)
		return (NULL);
	while (str[*i] && !(is_space(str[*i])) && !(is_operator(str[*i])))
		word[a++] = str[(*i)++];
	word[a] = '\0';
	word_token = create_token(word, TOKEN_WORD, QUOTE_NONE, flags);
	free(word);
	return (word_token);
}
