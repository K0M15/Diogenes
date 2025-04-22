/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:14:16 by afelger           #+#    #+#             */
/*   Updated: 2024/10/15 17:12:30 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned long	counter;
	unsigned long	len;

	counter = 0;
	len = ft_strlen(s) + 1;
	while (counter < len)
	{
		if ((char) c == s[counter])
			return ((char *)&s[counter]);
		counter++;
	}
	return (0);
}
