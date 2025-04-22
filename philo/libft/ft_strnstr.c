/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:22:08 by afelger           #+#    #+#             */
/*   Updated: 2024/10/17 14:21:51 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, unsigned long n)
{
	unsigned long	c_haystack;
	unsigned long	c_needle;
	unsigned long	needle_length;

	needle_length = ft_strlen(needle);
	c_haystack = 0;
	if (!needle_length)
		return ((char *)haystack);
	while (haystack[c_haystack] && c_haystack < n)
	{
		c_needle = 0;
		while (needle[c_needle]
			&& haystack[c_haystack + c_needle] == needle[c_needle]
			&& c_haystack + c_needle < n)
			c_needle++;
		if (c_needle == needle_length)
			return ((char *)&haystack[c_haystack]);
		c_haystack++;
	}
	return (0);
}
