/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:26:02 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/02 12:03:01 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_exit(char **args, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->last_exit_status;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd(BOLD_GRAY "exit\n" RESET, 2);
	if (args[1] && !is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	else if (args[1])
		exit_code = str_to_exitcode(args[1]);
	restore_std_fds(shell);
	free_env(shell->env);
	free_ast(&shell->ast);
	free_array(args);
	rl_clear_history();
	exit(exit_code);
}

bool	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

int	str_to_exitcode(const char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (num > (LLONG_MAX / 10) || (num == LLONG_MAX / 10
				&& (*str - '0') > LLONG_MAX % 10))
			return (255);
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)(num * sign) & 0xFF);
}
