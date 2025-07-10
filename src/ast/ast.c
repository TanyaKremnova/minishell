/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:31:35 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/26 14:36:28 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	left = parse_redirections(tokens, left);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_right_command(tokens, left);
		if (!right)
			return (NULL);
		left = create_pipe_node(left, right, tokens);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*parse_right_command(t_token **tokens, t_ast *left)
{
	t_ast	*right;

	right = parse_command(tokens);
	if (!right)
	{
		free_ast(&left);
		free_tokens(tokens);
		return (NULL);
	}
	right = parse_redirections(tokens, right);
	return (right);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right, t_token **tokens)
{
	t_ast	*pipe_node;

	pipe_node = new_ast_node(AST_PIPE);
	if (!pipe_node)
	{
		free_ast(&left);
		free_ast(&right);
		free_tokens(tokens);
		return (NULL);
	}
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast	*parse_redirections(t_token **tokens, t_ast *cmd_node)
{
	int	redir_type;

	while (*tokens && (*tokens)->group == GROUP_REDIRECT)
	{
		redir_type = (*tokens)->type;
		*tokens = (*tokens)->next;
		if (*tokens)
		{
			add_redirection(cmd_node, redir_type, (*tokens)->value,
				(*tokens)->flags.quoted);
			*tokens = (*tokens)->next;
		}
	}
	return (cmd_node);
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd_node;

	if (!*tokens)
		return (NULL);
	cmd_node = new_ast_node(AST_CMD);
	if (!cmd_node)
		return (NULL);
	if (!parse_cmd_tokens(tokens, cmd_node))
		return (free_incomplete_node(&cmd_node));
	return (cmd_node);
}
