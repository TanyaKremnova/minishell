/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:55:48 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/26 18:02:55 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*redirect_tokens(char *str, int *i)
{
	t_token			*redir_token;
	char			*word;
	t_token_flags	flags;

	redir_token = NULL;
	word = find_redirect(str, i);
	flags = (t_token_flags){.quoted = false, .glued = false};
	if (!word)
		return (NULL);
	if (word[0] == '<' && !(word[1]))
		redir_token = create_token(word, TOKEN_REDIRECT_IN, QUOTE_NONE, flags);
	else if (word[0] == '>' && !(word[1]))
		redir_token = create_token(word, TOKEN_REDIRECT_OUT, QUOTE_NONE, flags);
	else if (word[0] == '>' && word[1] == '>' && !(word[2]))
		redir_token = create_token(word, TOKEN_REDIRECT_APPEND, QUOTE_NONE,
				flags);
	else if (word[0] == '<' && word[1] == '<' && !(word[2]))
		redir_token = create_token(word, TOKEN_HEREDOC, QUOTE_NONE, flags);
	else
		return (NULL);
	redir_token->group = GROUP_REDIRECT;
	return (redir_token);
}

char	*find_redirect(char *str, int *i)
{
	static char	word[3];
	int			a;
	int			max;

	a = 0;
	max = 2;
	if (str[*i] == '<')
	{
		while (str[*i] && a < max && str[*i] == '<')
			word[a++] = str[(*i)++];
	}
	else if (str[*i] == '>')
	{
		while (str[*i] && a < max && str[*i] == '>')
			word[a++] = str[(*i)++];
	}
	word[a++] = '\0';
	return (word);
}
