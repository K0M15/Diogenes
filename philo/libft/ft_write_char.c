/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:28:49 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 08:54:16 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	writeout_char(va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	if (write(ft_printf_get_fd(), &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_printf_set_fd(int fd)
{
	static int	current_fd;

	if (current_fd == 0)
		current_fd = 1;
	if (fd < 0)
		return (current_fd);
	current_fd = fd;
	return (fd);
}

int	ft_printf_get_fd(void)
{
	return (ft_printf_set_fd(-1));
}
