/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:26:30 by tkremnov          #+#    #+#             */
/*   Updated: 2025/07/01 11:26:38 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(t_arg *arg, t_shell *shell)
{
	bool	nl;

	nl = true;
	while (arg && is_n_flag(arg->value))
	{
		nl = false;
		arg = arg->next;
	}
	print_echo_arguments(arg, shell);
	if (nl)
		write(1, "\n", 1);
	shell->last_exit_status = 0;
}

void	print_echo_arguments(t_arg *arg, t_shell *shell)
{
	char	*expanded;

	while (arg)
	{
		if (arg->quote_type == QUOTE_SINGLE)
			write(1, arg->value, ft_strlen(arg->value));
		else
		{
			expanded = replase_exit_status(arg->value, shell->last_exit_status);
			if (expanded)
			{
				write(1, expanded, ft_strlen(expanded));
				free(expanded);
			}
		}
		if (arg->next)
			write(1, " ", 1);
		arg = arg->next;
	}
}

char	*replase_exit_status(const char *arg, int status)
{
	char	*status_str;
	char	*result;
	size_t	len;
	int		count;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	count = count_exit_vars(arg);
	len = ft_strlen(arg) + count * (ft_strlen(status_str) - 2);
	result = malloc(len + 1);
	if (!result)
	{
		free(status_str);
		return (NULL);
	}
	result[0] = '\0';
	expand_status_loop(arg, result, status_str);
	free(status_str);
	return (result);
}

void	expand_status_loop(const char *arg, char *result,
			const char *status_str)
{
	const char	*tmp;

	tmp = arg;
	while (*tmp)
	{
		if (tmp[0] == '$' && tmp[1] == '?')
		{
			ft_strcat(result, status_str);
			tmp += 2;
		}
		else
		{
			append_char(result, tmp);
			tmp++;
		}
	}
}
