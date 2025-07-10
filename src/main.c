/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:30:34 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/04 09:48:00 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int malloc_counter = 0;
// static int fail_at = -1;

// void	set_malloc_fail(int fail_number)// TODO delete
// {
// 	fail_at = fail_number;
// }

// void	*my_malloc(size_t size)// TODO delete
// {
// 	if (fail_at >= 0 && malloc_counter == fail_at)
// 	{
// 		printf("Simulating malloc fail at allocation #%d\n", malloc_counter);
// 		return (NULL);
// 	}
// 	malloc_counter++;
// 	return (malloc(size));
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	// if (argc > 1) // TODO delete
	// 	set_malloc_fail(atoi(argv[1])); // TODO delete
	(void)argv;
	initiate_shell(&shell, envp);
	if (argc == 1)
		minishell_loop(&shell);
	free_shell(&shell);
	return (shell.last_exit_status);
}
