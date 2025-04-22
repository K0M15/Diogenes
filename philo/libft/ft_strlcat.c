/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:02 by afelger           #+#    #+#             */
/*   Updated: 2024/10/16 14:32:15 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_strlcat(char *dst, const char *src, unsigned long dsize)
{
	unsigned long	src_ctr;
	unsigned long	dst_ctr;
	unsigned long	result;

	src_ctr = 0;
	dst_ctr = ft_strlen(dst);
	if (dst_ctr < dsize)
		result = dst_ctr;
	else
		result = dsize;
	while (dst_ctr + 1 < dsize && src[src_ctr] && dsize)
	{
		dst[dst_ctr] = src[src_ctr];
		dst_ctr++;
		src_ctr++;
	}
	if (dst_ctr < dsize)
		dst[dst_ctr] = 0;
	return (result + ft_strlen(src));
}
