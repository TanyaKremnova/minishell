/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:44 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/04 09:33:27 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initiate_shell(t_shell	*shell, char **envp)
{
	shell->last_exit_status = 0;
	shell->heredoc_interrupted = 0;
	shell->interrupted = 0;
	shell->count = 0;
	shell->rl = NULL;
	shell->ast = NULL;
	shell->saved_stdout = -1;
	shell->saved_stdin = -1;
	shell->env = copy_env(envp);
	if (!shell->env)
		exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_shell(t_shell *shell)
{
	free_array(shell->env);
	shell->env = NULL;
	if (shell->rl)
	{
		free(shell->rl);
		shell->rl = NULL;
	}
	if (shell->saved_stdout > 2)
	{
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
	if (shell->saved_stdin > 2)
	{
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
	rl_clear_history();
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		free(env[i++]);
	free(env);
}
