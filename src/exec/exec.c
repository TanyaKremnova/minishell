/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:40 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 13:28:05 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (ast->type == AST_PIPE)
		handle_pipe(ast, shell);
	else if (ast->type == AST_CMD)
		execute_command_node(ast, shell);
}

bool	merge_glue_args(t_ast *ast)
{
	t_arg	*cur;
	t_arg	*next;
	char	*joined;

	cur = ast->args;
	while (cur && cur->next)
	{
		next = cur->next;
		if (next->glued)
		{
			joined = ft_strjoin(cur->value, next->value);
			if (!joined)
				return (false);
			free(cur->value);
			cur->value = joined;
			cur->next = next->next;
			free(next->value);
			free(next);
			continue ;
		}
		cur = cur->next;
	}
	return (true);
}

void	execute_command_node(t_ast *ast, t_shell *shell)
{
	if (save_std_fds(shell) != 0)
		return ;
	if (handle_redirections(ast->redirections, shell) != 0)
	{
		shell->last_exit_status = 1;
		restore_std_fds(shell);
		return ;
	}
	expand_args(ast, shell);
	if (!merge_glue_args(ast))
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (!ast->args || !ast->args->value)
		shell->last_exit_status = 0;
	else if (is_builtin(ast->args->value))
		handle_buildin(ast, shell);
	else
		handle_command(ast, shell);
	restore_std_fds(shell);
}
