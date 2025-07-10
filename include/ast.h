/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:06:56 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/27 16:07:39 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "token.h"

/**
 * @enum e_ast_type
 * @brief Enumerated type of AST
 * 
 * @param AST_PIPE 0. Pipe |
 * @param AST_CMD 1. Commands ("cat", "grep", "sort")
 */
typedef enum e_ast_type
{
	AST_PIPE,
	AST_CMD
}	t_ast_type;

/**
 * @struct s_redir
 * @brief Represents a single redirection in a command.
 * 
 * @param type Redirection token type
 * @param file Target file or delimiter associated with this redirection.
 * @param quoted True if the file/delimiter was quoted
 * (affects variable expansion behavior).
 * @param next  Pointer to the next argument in the list.
 */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	bool			quoted;
	struct s_redir	*next;
}					t_redir;

/**
 * @struct s_arg
 * @brief Represents a single argument in a command's argument list.
 * 
 * @param value The string value of this argument.
 * @param quote_type The type of quote that surrounded the value.
 * @param glued True if this argument is glued to the previous one without
 * a space.
 * @param next  Pointer to the next argument in the list.
 */
typedef struct s_arg
{
	char			*value;
	t_quote_type	quote_type;
	bool			glued;
	struct s_arg	*next;
}					t_arg;

/**
 * @struct s_ast
 * @brief Represents a node in the Abstract Syntax Tree (AST).
 * 
 * @param type Type of AST node (command, pipe, redirection).
 * @param args Linked list of arguments (command name, argument).
 * @param redirections Linked list of redirections.
 * @param left Used for pipes (e.g., left and right commands).
 * @param right Used for pipes (e.g., left and right commands).
 */
typedef struct s_ast
{
	t_ast_type		type;
	t_arg			*args;
	t_redir			*redirections;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/* ast */
t_ast	*parse_pipeline(t_token **tokens);
t_ast	*parse_right_command(t_token **tokens, t_ast *left);
t_ast	*create_pipe_node(t_ast *left, t_ast *right, t_token **tokens);
t_ast	*parse_redirections(t_token **tokens, t_ast *cmd_node);
t_ast	*parse_command(t_token **tokens);

/* ast_malloc */
t_ast	*new_ast_node(t_ast_type type);
bool	parse_cmd_tokens(t_token **tokens, t_ast *cmd_node);
bool	ast_append_arg_str(t_ast *ast, const char *value,
			t_quote_type quote_type, bool glued);
int		add_redirection(t_ast *cmd_node, t_token_type type, char *file,
			bool quoted);

/* free_ast */
void	free_args(t_arg *args);
void	free_redirections(t_redir *redirections);
void	free_ast(t_ast **ast);
char	*ft_strjoin_free(char *s1, char *s2);

/* ast_util */
t_ast	*free_incomplete_node(t_ast **ast);
bool	valid_token_for_redir(t_token_type type);
bool	valid_token_for_args(t_token_type type);

#endif