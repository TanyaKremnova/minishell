/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_build_in.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tkremnov <tkremnov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 16:57:08 by tkremnov      #+#    #+#                 */
/*   Updated: 2025/07/02 13:52:17 by lperekhr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BUILD_IN_H
# define EXEC_BUILD_IN_H
# include "ast.h"

/* execute_cd */
void	execute_cd(char **args, t_shell *shell);
char	*get_cd_target(char **args, t_shell *shell);
int		get_current_or_env_pwd(char *buffer, t_shell *shell);

/* execute_cd_util */
void	update_new_pwd(char *newpwd, t_shell *shell);
char	**add_to_env(char **env, const char *new_var);
void	update_env_var(t_shell *shell, const char *key, const char *value);

/* exec_echo */
void	execute_echo(t_arg *arg, t_shell *shell);
void	print_echo_arguments(t_arg *arg, t_shell *shell);
char	*replase_exit_status(const char *arg, int status);
void	expand_status_loop(const char *arg, char *result,
			const char *status_str);

/* exec_echo_utils */
bool	is_n_flag(char *s);
int		count_exit_vars(const char *arg);
void	append_char(char *result, const char *tmp);

/* execute_env */
void	execute_env(t_shell *shell);
int		env_len(char **envp);
char	**copy_env(char **envp);

/* execute_exit */
void	execute_exit(char **args, t_shell *shell);
bool	is_numeric(const char *str);
int		str_to_exitcode(const char *str);

/* execute_export */
void	execute_export(char **args, t_shell *shell);
void	export_error(char *arg, t_shell *shell);
bool	handle_export_pair(char **args, int *i, t_shell *shell);

/* execute_export_util0 */
void	print_export_list(char **env);
size_t	get_key_length(const char *var, bool is_append);
char	**copy_env_add(char **env, const char *new_var);
void	add_update_env(char ***env, const char *var);

/* execute_export_util1 */
bool	is_valid_identifier(const char *str);
bool	has_plus_equal(const char *str);
void	sort_env_array(char **env);
bool	is_append_var(const char *var);

/* execute_export_util2 */
bool	replace_env_value(char **env_entry, const char *var);
char	*get_old_env_value(const char *entry);
char	*join_env_pieces(const char *old, const char *append);
bool	append_env_value(char **env_entry, const char *var, size_t key_len);
bool	update_existing_env(char ***env, const char *var, size_t key_len,
			bool is_append);

/* execute_pwd */
void	execute_pwd(t_shell *shell);

/* execute_unset */
void	execute_unset(char **args, t_shell *shell);
void	remove_env_var(char ***env, const char *key);

#endif