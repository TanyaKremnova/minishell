/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:04 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 12:26:04 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_null(t_shell *shell)
{
	if (!shell->rl)
	{
		printf(BOLD_GRAY "exit\n" RESET);
		return (0);
	}
	if (*shell->rl)
		add_history(shell->rl);
	return (1);
}

void	reset_readline(t_shell *shell)
{
	if (shell->rl)
	{
		free(shell->rl);
		shell->rl = NULL;
	}
}
