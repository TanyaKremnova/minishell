/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:58:43 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/27 12:09:27 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	analyze_syntax(t_token *tokens, t_shell *shell)
{
	t_token		*curr;
	t_token		*prev;
	const char	*token_value;

	prev = NULL;
	token_value = NULL;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_WORD && (!ft_strcmp(curr->value, "&&")))
			return (print_syntax_error("&&", shell));
		if (curr->type == TOKEN_PIPE && curr->next
			&& curr->next->type == TOKEN_PIPE)
			return (print_syntax_error("|", shell));
		if (is_invalid_token_sequence(curr, prev))
		{
			token_value = invalid_token(curr);
			return (print_syntax_error(token_value, shell));
		}
		prev = curr;
		curr = curr->next;
	}
	prepare_heredoc(tokens);
	return (true);
}

bool	is_invalid_token_sequence(t_token *curr, t_token *prev)
{
	if (!curr)
		return (false);
	if (curr->group == GROUP_REDIRECT)
	{
		if (!curr->next
			|| (curr->next->type != TOKEN_WORD
				&& curr->next->type != TOKEN_DOUBLE_QUOTES
				&& curr->next->type != TOKEN_SINGLE_QUOTES
				&& curr->next->type != TOKEN_ENV_VARIABLE))
		{
			return (true);
		}
	}
	if (curr->type == TOKEN_PIPE)
	{
		if (!prev || prev->type == TOKEN_PIPE || !curr->next)
			return (true);
	}
	return (false);
}

const char	*invalid_token(t_token *curr)
{
	const char	*token_value;

	if (!curr->next)
		token_value = "newline";
	else if (curr->group == GROUP_REDIRECT)
		token_value = curr->next->value;
	else
		token_value = curr->value;
	return (token_value);
}

bool	print_syntax_error(const char *token, t_shell *shell)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	shell->last_exit_status = 2;
	return (false);
}

void	prepare_heredoc(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->type == TOKEN_HEREDOC
				&& (tokens->next->type == TOKEN_DOUBLE_QUOTES
					|| tokens->next->type == TOKEN_SINGLE_QUOTES
					|| tokens->next->type == TOKEN_ENV_VARIABLE)))
			tokens->next->type = TOKEN_WORD;
		tokens = tokens->next;
	}
}
