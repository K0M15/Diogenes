/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:20:44 by afelger           #+#    #+#             */
/*   Updated: 2025/03/26 17:50:01 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, unsigned long n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr++ = (unsigned char) c;
	}
	return (s);
}
