/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:55:22 by tkremnov          #+#    #+#             */
/*   Updated: 2024/10/23 13:20:18 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		chr;
	size_t		len;

	chr = (char)c;
	if (ft_strchr(s, c) == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == chr)
			return ((char *)&s[len]);
		len--;
	}
	if (s[0] == chr)
		return ((char *)s);
	if (chr == '\0')
	{
		return ((char *)&s[ft_strlen(s)]);
	}
	return (NULL);
}
