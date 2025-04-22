/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:06:14 by afelger           #+#    #+#             */
/*   Updated: 2024/10/15 10:11:42 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_calloc(unsigned int count, unsigned int size)
{
	char	*data;

	data = malloc(count * size);
	if (data == NULL)
		return (NULL);
	ft_memset(data, 0, count * size);
	return (data);
}
