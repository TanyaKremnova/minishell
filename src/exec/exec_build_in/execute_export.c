/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tkremnov <tkremnov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 13:28:40 by tkremnov      #+#    #+#                 */
/*   Updated: 2025/07/02 13:51:15 by lperekhr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(char **args, t_shell *shell)
{
	int	i;

	shell->last_exit_status = 0;
	if (!args[1])
		return (print_export_list(shell->env));
	i = 1;
	while (args[i])
	{
		if (args[i + 1] && (args[i + 1][0] != '\0')
			&& args[i][ft_strlen(args[i]) - 1] == '=')
		{
			if (!handle_export_pair(args, &i, shell))
			{
				shell->last_exit_status = 1;
				return ;
			}
			continue ;
		}
		if (is_valid_identifier(args[i]))
			add_update_env(&(shell->env), args[i]);
		else
			export_error(args[i], shell);
		i++;
	}
}

void	export_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->last_exit_status = 1;
}

bool	handle_export_pair(char **args, int *i, t_shell *shell)
{
	char	*joined;

	joined = ft_strjoin(args[*i], args[*i + 1]);
	if (!joined)
		return (false);
	if (is_valid_identifier(joined))
		add_update_env(&(shell->env), joined);
	else
		export_error(args[*i], shell);
	free(joined);
	(*i) += 2;
	return (true);
}
