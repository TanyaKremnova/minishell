/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tkremnov <tkremnov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 15:18:24 by tkremnov      #+#    #+#                 */
/*   Updated: 2025/07/02 13:53:43 by lperekhr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_args(t_ast *ast, t_shell *shell)
{
	t_arg	*arg;
	char	*expanded;

	arg = ast->args;
	while (arg)
	{
		if (arg->quote_type != QUOTE_SINGLE)
		{
			expanded = expand_value(arg->value, shell);
			if (!expanded)
			{
				expanded = ft_strdup("");
				if (!expanded)
				{
					shell->last_exit_status = 1;
					return ;
				}
			}
			free(arg->value);
			arg->value = expanded;
		}
		arg = arg->next;
	}
}

char	*expand_value(const char *str, t_shell *shell)
{
	char	*result;

	if (!str)
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = expand_loop(str, shell, result);
	return (result);
}

char	*expand_loop(const char *str, t_shell *shell, char *result)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = process_variable(str, &i, shell, result);
			if (!tmp)
				return (free(result), NULL);
			result = tmp;
		}
		else
		{
			tmp = ft_strjoin_char_free(result, str[i]);
			if (!tmp)
				return (free(result), NULL);
			result = tmp;
			i++;
		}
	}
	return (result);
}

char	*process_variable(const char *str, int *i, t_shell *shell, char *result)
{
	char	*tmp;

	(*i)++;
	if (str[*i] == '?')
	{
		tmp = expand_exit_status(result, shell->last_exit_status);
		if (!tmp)
			return (NULL);
		result = tmp;
		(*i)++;
	}
	else
	{
		tmp = expand_normal_variable(str, i, shell, result);
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	return (result);
}
