/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:02:17 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/26 15:51:08 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*command;

	command = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	paths = find_path(env);
	if (!paths)
		return (NULL);
	command = get_command(cmd, paths);
	if (!command)
	{
		free_array(paths);
		return (NULL);
	}
	free_array(paths);
	return (command);
}

char	**find_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_command(char *cmd, char **path)
{
	int		i;
	char	*temp;
	char	*command;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (NULL);
		command = ft_strjoin(temp, cmd);
		if (!command)
			return (free(temp), NULL);
		free(temp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}
