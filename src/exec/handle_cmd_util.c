/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:20:47 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 12:42:00 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_arg *curr)
{
	int	args_count;

	args_count = 0;
	while (curr)
	{
		curr = curr->next;
		args_count++;
	}
	return (args_count);
}

void	free_cmd_and_path(char **cmd, char *path)
{
	free_array(cmd);
	free(path);
}

int	check_command_access(char *path)
{
	struct stat	info;

	if (stat(path, &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			return (126);
		if (access(path, X_OK) != 0)
			return (126);
	}
	return (0);
}

void	print_permission_error(char *path, t_exec_cmd *cmd, t_shell *shell)
{
	struct stat	info;

	if (stat(path, &info) == 0 && S_ISDIR(info.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
	}
	else
		perror("minishell");
	free_cmd_and_path(cmd->cmd, cmd->path);
	free_ast(&shell->ast);
	free_env(shell->env);
	rl_clear_history();
	exit(126);
}

void	short_command(char *dest, size_t dest_size, const char *cmd)
{
	size_t	len;

	if (dest_size == 0)
		return ;
	dest[0] = '\0';
	len = ft_strlen(cmd);
	ft_strlcpy(dest, "minishell: ", dest_size);
	if (len > CMD_DISPLAY_LIMIT)
	{
		if (dest_size < MIN_REQUIRED_LEN)
		{
			dest[0] = '\0';
			return ;
		}
		ft_strlcat(dest, cmd, dest_size);
		dest[MINISHELL_LEN + TRIMMED_CMD_LEN] = '\0';
		ft_strlcat(dest, "...", dest_size);
	}
	else
		ft_strlcat(dest, cmd, dest_size);
	ft_strlcat(dest, ": command not found\n", dest_size);
}
