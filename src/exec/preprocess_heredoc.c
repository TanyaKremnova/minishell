/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   preprocess_heredoc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tkremnov <tkremnov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 13:09:20 by lperekhr      #+#    #+#                 */
/*   Updated: 2025/07/01 10:55:30 by lperekhr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	preprocess_heredocs(t_ast *ast, t_shell *shell)
{
	t_redir	*redir;

	if (!ast)
		return ;
	if (shell->heredoc_interrupted)
		return ;
	redir = ast->redirections;
	if (ast->type == AST_PIPE)
	{
		preprocess_heredocs(ast->left, shell);
		preprocess_heredocs(ast->right, shell);
	}
	else if (ast->type == AST_CMD)
	{
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				prepare_heredocs(shell, redir);
			if (shell->heredoc_interrupted)
				return ;
			redir = redir->next;
		}
	}
}

void	prepare_heredocs(t_shell *shell, t_redir *redir)
{
	char		*temp_file;

	temp_file = create_heredoc_file(shell, redir);
	if (!temp_file)
	{
		shell->last_exit_status = 130;
		return ;
	}
	if (shell->heredoc_interrupted)
	{
		unlink(temp_file);
		free(temp_file);
		return ;
	}
	free(redir->file);
	redir->file = temp_file;
	redir->type = TOKEN_REDIRECT_IN;
}

char	*create_heredoc_file(t_shell *shell, t_redir *redir)
{
	char	*filename;
	int		fd;

	filename = get_heredoc_filename(shell);
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(filename), NULL);
	setup_signals_special();
	heredoc_read_loop(fd, redir, shell);
	close(fd);
	setup_signals();
	if (shell->heredoc_interrupted == 1)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	shell->count++;
	return (filename);
}
