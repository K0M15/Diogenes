/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:21:09 by afelger           #+#    #+#             */
/*   Updated: 2024/10/15 15:46:53 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, unsigned long n)
{
	unsigned int	counter;
	unsigned char	*str;
	unsigned char	c2;

	str = (unsigned char *)s;
	c2 = (unsigned char)c;
	counter = 0;
	while (counter < n)
	{
		if (str[counter] == c2)
			return (((void *)&str[counter]));
		counter++;
	}
	return (0);
}
