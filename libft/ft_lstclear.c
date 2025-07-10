/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:22:52 by tkremnov          #+#    #+#             */
/*   Updated: 2024/10/23 14:09:08 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
	{
		return ;
	}
	while (*lst)
	{
		temp = (*lst)->next;
		if (del != NULL)
		{
			del((*lst)->content);
		}
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
