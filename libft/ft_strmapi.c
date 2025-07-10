/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:22:38 by tkremnov          #+#    #+#             */
/*   Updated: 2024/10/23 12:08:00 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*duplicate;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	duplicate = ft_strdup(s);
	if (!duplicate)
		return (NULL);
	i = 0;
	while (duplicate[i])
	{
		duplicate[i] = f(i, duplicate[i]);
		i++;
	}
	return (duplicate);
}
