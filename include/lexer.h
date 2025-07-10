/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:38 by lperekhr          #+#    #+#             */
/*   Updated: 2025/07/01 13:31:23 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"

/* lexer */
t_token		*lexer(const char *str, int i, int prev_token_end, t_shell *shell);
t_token		*lexer_tokens(const char *str, int *i, int prev_token_end,
				t_shell *shell);

/* whatever_tokens */
t_token		*dollar_token(char *str, int *i, int prev_i, const char *full_str);
t_token		*env_variable_token(int *i, int prev_i, const char *full_str);
t_token		*pipe_token(char *str, int *i);
t_token		*word_token(char *str, int *i, int prev_i, const char *full_str);

/* quotes_token */
t_token		*quotes_token(char *str, int *i, int prev_i, const char *full_str);
char		*find_quotes(char *str, int *i);

/* redirect_tokens */
t_token		*redirect_tokens(char *str, int *i);
char		*find_redirect(char *str, int *i);

/* lexer_util */
bool		is_space(char c);
bool		is_operator(char c);
bool		is_glued(const char *str, int prev_end, int curr_start);

/* analyze_syntax */
bool		analyze_syntax(t_token *tokens, t_shell *shell);
bool		is_invalid_token_sequence(t_token *curr, t_token *prev);
const char	*invalid_token(t_token *curr);
bool		print_syntax_error(const char *token, t_shell *shell);
void		prepare_heredoc(t_token *tokens);

#endif