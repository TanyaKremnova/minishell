/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_defs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:15:21 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 11:15:05 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DEFS_H
# define SHELL_DEFS_H

struct	s_ast;

/**
 * @struct s_shell
 * @brief Represents the state of the minishell during execution.
 * 
 * @param last_exit_status Stores the exit status of the last executed command.
 * @param heredoc_interrupted Set to 1 if a heredoc was interrupted
 * (e.g., Ctrl+C).
 * @param interrupted General interrupt flag used for signal handling.
 * @param count Counter used for generating unique heredoc filenames.
 * @param env Environment variables as a NULL-terminated array of strings.
 * @param rl Stores the most recent readline input (used for memory management).
 * @param ast Pointer to the root of the abstract syntax tree (AST)
 * for the parsed input.
 */
typedef struct s_shell
{
	int				last_exit_status;
	int				heredoc_interrupted;
	int				interrupted;
	int				count;
	char			**env;
	char			*rl;
	struct s_ast	*ast;
	int				saved_stdout;
	int				saved_stdin;
}	t_shell;

/**
 * @enum e_quote_type
 * @brief Represents the type of quoting applied to a shell token.
 * 
 * @param QUOTE_NONE No quotes are applied to the token.
 * @param QUOTE_SINGLE Token is enclosed in single quotes ('),
 * no expansion occurs.
 * @param QUOTE_DOUBLE Token is enclosed in double quotes ("),
 * allowing variable expansion.
 */
typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

#endif