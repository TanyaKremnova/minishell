/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:56:01 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 13:18:34 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "ast.h"

/**
 * @struct s_exec_cmd
 * @brief Represents an executable shell command.
 * 
 * @param cmd NULL-terminated array of strings representing the command
 * and its arguments.
 * @param path Full path to the executable binary (resolved via PATH
 * or given directly).
 */
typedef struct s_exec_cmd
{
	char	**cmd;
	char	*path;
}	t_exec_cmd;

/* preprocess heredoc */
void	preprocess_heredocs(t_ast *ast, t_shell *shell);
void	prepare_heredocs(t_shell *shell, t_redir *redir);
char	*create_heredoc_file(t_shell *shell, t_redir *redir);

/* preprocess heredoc utils */
char	*get_heredoc_filename(t_shell *shell);
void	heredoc_read_loop(int fd, t_redir *redir, t_shell *shell);
bool	process_heredoc_line(char *line, int fd,
			t_redir *redir, t_shell *shell);
void	print_heredoc_eof_warning(char *delimiter);

/* exec */
void	execute_ast(t_ast *ast, t_shell *shell);
bool	merge_glue_args(t_ast *ast);
void	execute_command_node(t_ast *ast, t_shell *shell);

/* exec_util */
void	set_exit_status_waitpid(int status, t_shell *shell);
int		save_std_fds(t_shell *shell);
void	restore_std_fds(t_shell *shell);

/* expand_args */
void	expand_args(t_ast *ast, t_shell *shell);
char	*expand_value(const char *str, t_shell *shell);
char	*expand_loop(const char *str, t_shell *shell, char *result);
char	*process_variable(const char *str, int *i, t_shell *shell,
			char *result);

/* expand_args_utils */
char	*expand_exit_status(char *result, int last_exit_status);
char	*expand_normal_variable(const char *str, int *i, t_shell *shell,
			char *result);
char	*ft_strjoin_char_free(char *s, char c);
int		read_var_name(const char *str, int i, char *var_name);
char	*get_env_value(char **env, const char *key);

/* handle_cmd */
char	**build_cmd(t_arg *args);
void	handle_command(t_ast *ast, t_shell *shell);
bool	prepare_command_and_path(t_exec_cmd *cmd, t_ast *ast, t_shell *shell);
void	handle_fork_result(pid_t pid, t_ast *ast, t_shell *shell,
			t_exec_cmd *cmd);
void	handle_child_process(t_ast *ast, t_shell *shell, t_exec_cmd *cmd);

/* handle_cmd_util */
int		count_args(t_arg *curr);
void	free_cmd_and_path(char **cmd, char *path);
int		check_command_access(char *path);
void	print_permission_error(char *path, t_exec_cmd *cmd, t_shell *shell);
void	short_command(char *dest, size_t dest_size, const char *cmd);

/* handle_redirections */
int		handle_redirections(t_redir *redir, t_shell *shell);
int		expand_redir_file(t_redir *redir, t_shell *shell);
bool	is_heredoc(const char *filename);
int		handle_in(t_redir *redir, int fd);
int		handle_out_apnd(t_redir *redir, int fd);

/* find_command_path */
char	*find_command_path(char *cmd, char **env);
char	**find_path(char **env);
char	*get_command(char *cmd, char **path);

/* handle_buildin */
void	handle_buildin(t_ast *ast, t_shell *shell);
bool	is_builtin(const char *cmd);

/* handle_pipe */
int		handle_pipe(t_ast *ast, t_shell *shell);
pid_t	child_left(t_ast *left, int pipefd[2], t_shell *shell);
pid_t	child_right(t_ast *right, int pipefd[2], t_shell *shell);
int		handle_pipe_error(int *pipefd, pid_t pid1, t_shell *shell);
void	close_exit(int pipefd[2], int should_exit);

#endif