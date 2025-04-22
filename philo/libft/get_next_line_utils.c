/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:51:20 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 08:35:26 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_ft_strlen(char *str)
{
	int	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	gnl_ft_cleanup(char **remainder, char **str)
{
	if (*remainder != NULL)
	{
		free(*remainder);
		*remainder = NULL;
	}
	if (str != NULL)
	{
		if (*str != NULL)
			free(*str);
		*str = NULL;
	}
}

int	gnl_ft_has_char(char *str, char c, int *pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			*pos = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	gnl_cat_and_free(char **dest, char **src, int read_size)
{
	int		dest_len;
	char	*dest_new;
	int		c;
	int		i;

	dest_len = gnl_ft_strlen(*dest) + 1;
	dest_new = malloc(dest_len + read_size);
	if (dest_new == NULL)
		return (gnl_ft_cleanup(src, dest), 0);
	c = 0;
	while ((*dest)[c])
	{
		dest_new[c] = (*dest)[c];
		c++;
	}
	i = 0;
	while (i < read_size)
	{
		dest_new[c + i] = (*src)[i];
		i++;
	}
	dest_new[c + i] = 0;
	free(*dest);
	*dest = dest_new;
	return (1);
}
