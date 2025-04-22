/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:17:29 by afelger           #+#    #+#             */
/*   Updated: 2024/10/17 14:09:24 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned long n)
{
	unsigned long	counter;

	counter = 0;
	if (dest == 0 && src == 0)
		return (dest);
	if (dest < src)
	{
		while (counter < n)
		{
			((char *)dest)[counter] = ((char *)src)[counter];
			counter++;
		}
	}
	else
	{
		counter--;
		while (counter > --n)
		{
			((char *)dest)[n] = ((char *)src)[n];
		}
	}
	return (dest);
}
