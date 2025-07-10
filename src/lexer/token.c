/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:15 by lperekhr          #+#    #+#             */
/*   Updated: 2025/07/02 12:10:35 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *word, t_token_type type,
			t_quote_type quote_type, t_token_flags flags)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(word);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->group = GROUP_NONE;
	new_token->quote_type = quote_type;
	new_token->flags = flags;
	new_token->next = NULL;
	return (new_token);
}

void	free_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return ;
	free_token_list(*tokens);
	*tokens = NULL;
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}
