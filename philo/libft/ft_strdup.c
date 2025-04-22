/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:27 by afelger           #+#    #+#             */
/*   Updated: 2024/10/15 16:23:44 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strdup(const char *s1)
{
	char			*result;
	unsigned int	len;

	len = ft_strlen(s1) + 1;
	result = malloc(len);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len);
	return (result);
}
