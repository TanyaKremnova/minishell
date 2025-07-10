/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:00 by lperekhr          #+#    #+#             */
/*   Updated: 2025/07/04 09:46:27 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(const char *str, int i, int prev_token_end, t_shell *shell)
{
	t_token	*new_token;

	new_token = NULL;
	if (!str[i])
		return (NULL);
	if (is_space(str[i]))
		return (lexer(str, i + 1, prev_token_end, shell));
	new_token = lexer_tokens(str, &i, prev_token_end, shell);
	if (!new_token)
		return (NULL);
	new_token->next = lexer(str, i, i, shell);
	while (str[i] && is_space(str[i]))
		i++;
	if (new_token->next == NULL && str[i] != '\0')
	{
		free_tokens(&new_token);
		return (NULL);
	}
	return (new_token);
}

t_token	*lexer_tokens(const char *str, int *i, int prev_token_end,
			t_shell *shell)
{
	t_token	*token;

	if (!str[*i])
		return (NULL);
	if (is_space(str[*i]))
		return (NULL);
	if (str[*i] == '|')
		return (pipe_token((char *)str, i));
	if (str[*i] == '$')
		return (dollar_token((char *)str, i, prev_token_end, str));
	if (str[*i] && !(is_space(str[*i])) && !(is_operator(str[*i])))
		return (word_token((char *)str, i, prev_token_end, str));
	if (str[*i] == '<' || str[*i] == '>')
		return (redirect_tokens((char *)str, i));
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		token = quotes_token((char *)str, i, prev_token_end, str);
		if (!token)
			shell->last_exit_status = 2;
		return (token);
	}
	return (NULL);
}
