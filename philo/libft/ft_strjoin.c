/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:47 by afelger           #+#    #+#             */
/*   Updated: 2024/10/16 15:33:09 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	unsigned int	s1len;
	unsigned int	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len == 0 && s2len == 0)
		return (ft_calloc(1, 1));
	result = malloc(s1len + s2len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, s1len + 1);
	ft_strlcat(result, s2, s1len + s2len + 1);
	return (result);
}
