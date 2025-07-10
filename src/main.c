/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:30:34 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/10 11:54:04 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	initiate_shell(&shell, envp);
	if (argc == 1)
		minishell_loop(&shell);
	free_shell(&shell);
	return (shell.last_exit_status);
}
