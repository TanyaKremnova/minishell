/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:37 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 11:55:55 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_shell *shell)
{
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		setup_signals();
		shell->rl = readline(BOLD_MAG "minishell$ " RESET);
		if (!handle_input_null(shell))
			break ;
		if (g_signal == SIGINT)
		{
			shell->last_exit_status = 130;
			g_signal = 0;
		}
		if (!process_tokens_and_ast(shell, &tokens))
		{
			reset_readline(shell);
			free_tokens(&tokens);
			continue ;
		}
		execute_ast(shell->ast, shell);
		free_ast(&shell->ast);
		free_tokens(&tokens);
		reset_readline(shell);
	}
}

int	process_tokens_and_ast(t_shell *shell, t_token **tokens)
{
	if (!tokenize_input(shell, tokens))
		return (0);
	if (!validate_and_parse_ast(shell, tokens, &shell->ast))
		return (0);
	if (!handle_heredocs_and_signals(shell->ast, shell))
	{
		free_ast(&shell->ast);
		return (0);
	}
	return (1);
}

int	handle_heredocs_and_signals(t_ast *ast, t_shell *shell)
{
	preprocess_heredocs(ast, shell);
	if (shell->heredoc_interrupted)
	{
		shell->heredoc_interrupted = 0;
		g_signal = 0;
		reset_readline(shell);
		return (0);
	}
	return (1);
}

int	validate_and_parse_ast(t_shell *shell, t_token **tokens, t_ast **ast)
{
	t_token	*start_token_list;

	if (!tokens || !*tokens || !ast)
		return (0);
	start_token_list = *tokens;
	if (!analyze_syntax(*tokens, shell))
	{
		reset_readline(shell);
		return (0);
	}
	*ast = parse_pipeline(tokens);
	if (!*ast)
	{
		reset_readline(shell);
		return (0);
	}
	free_tokens(&start_token_list);
	return (1);
}

int	tokenize_input(t_shell *shell, t_token **tokens)
{
	*tokens = lexer(shell->rl, 0, -1, shell);
	if (!*tokens)
	{
		reset_readline(shell);
		return (0);
	}
	return (1);
}
