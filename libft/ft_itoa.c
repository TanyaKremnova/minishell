/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:56:44 by tkremnov          #+#    #+#             */
/*   Updated: 2024/10/23 10:39:58 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_length(int n);

char	*ft_itoa(int n)
{
	unsigned int		len;
	char				*str;
	long				num;

	len = get_length(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	num = (long)n;
	if (num < 0)
		num = -num;
	str[len] = '\0';
	while (len--)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

static unsigned int	get_length(int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
