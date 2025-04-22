/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:19:10 by afelger           #+#    #+#             */
/*   Updated: 2024/10/16 14:13:55 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_strlcpy(char *dst, const char *src, unsigned long dsize)
{
	unsigned long	counter;

	counter = 0;
	while (src[counter] && counter < dsize - 1 && dsize)
	{
		dst[counter] = src[counter];
		counter++;
	}
	if (counter < dsize)
		dst[counter] = 0;
	return (ft_strlen(src));
}
