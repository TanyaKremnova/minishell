/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tkremnov <tkremnov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 16:41:52 by tkremnov      #+#    #+#                 */
/*   Updated: 2025/07/02 13:53:35 by lperekhr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_redir *redir, t_shell *shell)
{
	int		fd;

	fd = 0;
	while (redir)
	{
		if (!redir->file)
		{
			perror("missing file");
			return (1);
		}
		if (expand_redir_file(redir, shell))
			return (1);
		if (redir->type == TOKEN_REDIRECT_IN)
		{
			if (handle_in(redir, fd))
				return (1);
		}
		else if (redir->type == TOKEN_REDIRECT_OUT
			|| redir->type == TOKEN_REDIRECT_APPEND)
			if (handle_out_apnd(redir, fd))
				return (1);
		redir = redir->next;
	}
	return (0);
}

int	expand_redir_file(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	if (redir->type == TOKEN_SINGLE_QUOTES)
		return (0);
	expanded = expand_value(redir->file, shell);
	if (!expanded)
	{
		expanded = ft_strdup("");
		if (!expanded)
		{
			shell->last_exit_status = 1;
			return (1);
		}
	}
	free(redir->file);
	redir->file = expanded;
	if (redir->file[0] == '\0')
	{
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	return (0);
}

bool	is_heredoc(const char *filename)
{
	return (ft_strncmp(filename, "/tmp/heredoc_tmp_", 17) == 0);
}

int	handle_in(t_redir *redir, int fd)
{
	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 in");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_out_apnd(t_redir *redir, int fd)
{
	if (redir->type == TOKEN_REDIRECT_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_REDIRECT_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 out");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
