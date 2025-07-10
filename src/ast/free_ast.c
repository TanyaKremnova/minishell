/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:35:21 by tkremnov          #+#    #+#             */
/*   Updated: 2025/06/26 14:37:13 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_arg *args)
{
	t_arg	*tmp;

	while (args)
	{
		tmp = args->next;
		if (args->value)
			free(args->value);
		free(args);
		args = tmp;
	}
}

void	free_redirections(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections)
	{
		tmp = redirections->next;
		if (redirections->file)
			free(redirections->file);
		free(redirections);
		redirections = tmp;
	}
}

void	free_ast(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);
	free_args((*ast)->args);
	free_redirections((*ast)->redirections);
	free(*ast);
	*ast = NULL;
}

static char	*safe_strdup(const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	return (dup);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (safe_strdup(s2));
	if (!s2)
		return (free(s1), NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (free(s1), NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2 + 1);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}
