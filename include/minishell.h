/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:21:15 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/04 09:48:12 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>	
# include <errno.h>

# include "shell_defs.h"
# include "signals.h"
# include "libft.h"
# include "token.h"
# include "lexer.h"
# include "ast.h"
# include "exec.h"
# include "exec_build_in.h"

//ANSI escape codes
// \001 marks the start of a non-printable section
// \002 marks the end of a non-printable section

// Foreground Color Code / (Background Color Code)
// 30 / (40)→ Black
// 31 / (41)→ Red
// 32 / (42)→ Green
// 33 / (43)→ Yellow
// 34 / (44)→ Blue
// 35 / (45)→ Magenta
// 36 / (46)→ Cyan
// 37 / (47)→ White

// 90 / (100)→ Bright Black
// 91 / (101)→ Bright Red
// 92 / (102)→ Bright Green
// 93 / (103)→ Bright Yellow
// 94 / (104)→ Bright Blue
// 95 / (105)→ Bright Magenta
// 96 / (106)→ Bright Cyan
// 97 / (107)→ Bright White

// # define malloc my_malloc //TODO delete
// void	*my_malloc(size_t size);  //TODO delete
// void	set_malloc_fail(int fail_number);  //TODO delete

# define BOLD_MAG "\001\033[1;35m\002"
# define BOLD_GRAY "\001\033[1;90m\002"
# define RESET "\001\033[0m\002"

# define SHELL_PATH_MAX 4096
# define EXEC_PATH_MAX 1024
# define CMD_DISPLAY_LIMIT 50
# define MINISHELL_LEN 11
# define MESSAGE_LEN 21
# define DOTS_LEN 3

/**
 * @brief Number of command characters to keep before adding ellipsis.
 * 
 * This is CMD_DISPLAY_LIMIT - DOTS_LEN (50 - 3),
 * because we reserve 3 characters for "...".
 */
# define TRIMMED_CMD_LEN 47

/**
 * @brief Minimum buffer size required to build the full error message.
 * 
 * Includes:
 * "minishell: " (11) + trimmed command (47) + "..." (3)
 * + ": command not found\n" (21) + null-terminator (1)
 * 
 * Total: 11 + 47 + 3 + 21 + 1 = 83
 */
# define MIN_REQUIRED_LEN 83

/* main utils */
void	initiate_shell(t_shell	*shell, char **envp);
void	free_array(char **array);
void	free_shell(t_shell *shell);
void	free_env(char **env);

/* minishell */
void	minishell_loop(t_shell *shell);
int		process_tokens_and_ast(t_shell *shell, t_token **tokens);
int		handle_heredocs_and_signals(t_ast *ast, t_shell *shell);
int		validate_and_parse_ast(t_shell *shell, t_token **tokens, t_ast **ast);
int		tokenize_input(t_shell *shell, t_token **tokens);

/* minishell utils */
int		handle_input_null(t_shell *shell);
void	reset_readline(t_shell *shell);

#endif