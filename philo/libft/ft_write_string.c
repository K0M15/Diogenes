/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:30:04 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 07:57:18 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	writeout_string(va_list ap)
{
	int		strl;
	char	*str;

	str = va_arg(ap, char *);
	strl = 0;
	if (str == NULL)
	{
		if (write(ft_printf_get_fd(), "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (str[strl])
		strl++;
	if (write(ft_printf_get_fd(), str, strl) == -1)
		return (-1);
	return (strl);
}
