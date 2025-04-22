/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:21:01 by afelger           #+#    #+#             */
/*   Updated: 2024/10/17 13:58:12 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned long n)
{
	unsigned int	counter;

	counter = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (counter < n)
	{
		((char *)dest)[counter] = ((char *)src)[counter];
		counter++;
	}
	return (dest);
}
