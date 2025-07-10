/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:55:15 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/04 09:45:32 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

bool	parse_cmd_tokens(t_token **tokens, t_ast *cmd_node)
{
	t_token	*redir_token;

	while (*tokens)
	{
		if (valid_token_for_redir((*tokens)->type))
		{
			redir_token = *tokens;
			*tokens = (*tokens)->next;
			if (!add_redirection(cmd_node, redir_token->type, (*tokens)->value,
					(*tokens)->flags.quoted))
				return (false);
			*tokens = (*tokens)->next;
		}
		else if (valid_token_for_args((*tokens)->type))
		{
			if (!ast_append_arg_str(cmd_node, (*tokens)->value,
					(*tokens)->quote_type, (*tokens)->flags.glued))
				return (free_ast(&cmd_node), false);
			*tokens = (*tokens)->next;
		}
		else
			break ;
	}
	return (true);
}

bool	ast_append_arg_str(t_ast *ast, const char *value,
			t_quote_type quote_type, bool glued)
{
	t_arg	*new_arg;
	t_arg	*tmp;

	if (!ast || !value)
		return (false);
	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		return (false);
	new_arg->value = ft_strdup(value);
	if (!new_arg->value)
		return (free(new_arg), false);
	new_arg->quote_type = quote_type;
	new_arg->glued = glued;
	new_arg->next = NULL;
	if (!ast->args)
		ast->args = new_arg;
	else
	{
		tmp = ast->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_arg;
	}
	return (true);
}

int	add_redirection(t_ast *cmd_node, t_token_type type, char *file, bool quoted)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	if (!cmd_node || !file)
		return (0);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
		return (free(new_redir), 0);
	new_redir->quoted = quoted;
	new_redir->next = NULL;
	if (!cmd_node->redirections)
		cmd_node->redirections = new_redir;
	else
	{
		tmp = cmd_node->redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
	return (1);
}
