/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:52 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/26 14:16:39 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/**
 * @enum e_token_type
 * @brief Enumerated type of TOKEN
 * 
 * @param TOKEN_WORD 0. Commands ("cat", "grep", "sort")
 * @param TOKEN_PIPE 1. Pipe |
 * @param TOKEN_REDIRECT_IN 2. Input redirection <
 * @param TOKEN_REDIRECT_OUT 3. Output redirection >
 * @param TOKEN_REDIRECT_APPEND 4. Output append redirection >>
 * @param TOKEN_HEREDOC 5. Heredoc redirection <<
 * @param TOKEN_SINGLE_QUOTES 6. Single quotes string '...'
 * @param TOKEN_DOUBLE_QUOTES 7. Double quotes string "..."
 * @param TOKEN_ENV_VARIABLE 8. Enviroment variable $VAR (echo $HOME)
 * @param TOKEN_EXIT_STATUS 9. For exit status (echo $?)
 */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTES,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_ENV_VARIABLE,
	TOKEN_EXIT_STATUS
}	t_token_type;

/**
 * @enum e_group
 * @brief Enumerated type of the tokens group
 * 
 * @param GROUP_REDIRECT 0. Group for redirections and heredoc tokens
 * @param GROUP_NONE 1. Default group for all tokens
 */
typedef enum e_group
{
	GROUP_REDIRECT,
	GROUP_NONE
}	t_group;

/**
 * @enum s_token_flags
 * @brief Represent an additional information about tokens
 * 
 * @param quoted To check if tokens are quoted
 * @param glued To check if tokens are glued
 */
typedef struct s_token_flags
{
	bool	quoted;
	bool	glued;
}			t_token_flags;

/**
 * @enum s_token
 * @brief Represent a token in lexical analysis
 * 
 * @param type Type of the token (command, pipe, redirection)
 * @param group To group all redirections and heredoc in one group
 * @param value Actual string from the input ("ls", ">", "file.txt")
 * @param next Pointer to next token, to connect and create tokens (linked list)
 */
typedef struct s_token
{
	t_token_type	type;
	t_group			group;
	t_quote_type	quote_type;
	t_token_flags	flags;
	char			*value;
	struct s_token	*next;
}					t_token;

/* token */
t_token	*create_token(char *word, t_token_type type,
			t_quote_type quote_type, t_token_flags flags);
void	free_tokens(t_token **tokens);
void	free_token_list(t_token *head);

#endif