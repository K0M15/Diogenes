/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:36 by afelger           #+#    #+#             */
/*   Updated: 2024/10/18 16:59:15 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char	*result;
	int		slen;

	if (len == 0 || start > ft_strlen(s))
		return (ft_calloc(1, 1));
	slen = (ft_strlen(&s[start]) < len) * ft_strlen(&s[start])
		+ (ft_strlen(&s[start]) >= len) * len;
	result = malloc(slen + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, &s[start], slen + 1);
	return (result);
}
