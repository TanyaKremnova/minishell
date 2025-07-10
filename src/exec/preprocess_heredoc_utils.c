/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_heredoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:24:55 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 13:29:28 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void);

char	*get_heredoc_filename(t_shell *shell)
{
	char	*filename;
	char	*num;

	num = ft_itoa(shell->count);
	if (!num)
		return (NULL);
	filename = ft_strjoin ("/tmp/heredoc_tmp_", num);
	free(num);
	return (filename);
}

static int	event(void)
{
	return (0);
}

void	heredoc_read_loop(int fd, t_redir *redir, t_shell *shell)
{
	char	*line;

	rl_event_hook = event;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_heredoc_eof_warning(redir->file);
			break ;
		}
		if (g_signal != 0)
		{
			g_signal = 0;
			shell->heredoc_interrupted = 1;
			free(line);
			break ;
		}
		if (!process_heredoc_line(line, fd, redir, shell))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

bool	process_heredoc_line(char *line, int fd,
			t_redir *redir, t_shell *shell)
{
	char	*expanded;

	if (ft_strcmp(line, redir->file) == 0)
		return (false);
	if (!redir->quoted)
	{
		expanded = expand_value(line, shell);
		if (expanded == NULL)
			return (false);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (true);
}

void	print_heredoc_eof_warning(char *delimiter)
{
	ft_putstr_fd(
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		STDOUT_FILENO);
	ft_putstr_fd(delimiter, STDOUT_FILENO);
	ft_putstr_fd("')\n", STDOUT_FILENO);
}
