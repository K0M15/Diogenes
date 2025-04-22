/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:14:18 by afelger           #+#    #+#             */
/*   Updated: 2024/10/18 16:40:14 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned long n)
{
	unsigned long		counter;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	counter = 0;
	if (n == 0)
		return (0);
	while (counter + 1 < n && str1[counter] - str2[counter] == 0
		&& str1[counter] && str2[counter])
		counter++;
	return (str1[counter] - str2[counter]);
}
