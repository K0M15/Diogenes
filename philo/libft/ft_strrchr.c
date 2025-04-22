/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:14:17 by afelger           #+#    #+#             */
/*   Updated: 2024/10/17 16:04:11 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned long	counter;

	counter = ft_strlen(s);
	if (!(char)c)
		return ((char *)s + counter);
	while (counter > 0)
	{
		if ((char)c == (char)(*(s + counter)))
			return ((char *)(s + counter));
		counter--;
	}
	if ((char)c == (char)(*(s)))
		return ((char *)(s));
	return (0);
}
