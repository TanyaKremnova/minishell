/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:30:41 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/24 10:04:30 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*free_incomplete_node(t_ast **ast)
{
	if (!ast || !*ast)
		return (NULL);
	free_args((*ast)->args);
	free_redirections((*ast)->redirections);
	free(*ast);
	*ast = NULL;
	return (NULL);
}

bool	valid_token_for_redir(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_HEREDOC);
}

bool	valid_token_for_args(t_token_type type)
{
	return (type == TOKEN_WORD
		|| type == TOKEN_DOUBLE_QUOTES
		|| type == TOKEN_SINGLE_QUOTES
		|| type == TOKEN_ENV_VARIABLE
		|| type == TOKEN_EXIT_STATUS);
}
