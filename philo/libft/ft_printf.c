/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:49:17 by afelger           #+#    #+#             */
/*   Updated: 2024/10/21 09:37:38 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_conversion(char fmt, va_list ap);

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;
	int		func_written;

	va_start(ap, str);
	count = 0;
	while (*str)
	{
		if (*str != '%')
		{
			func_written = write(1, str, 1);
		}
		else
		{
			str++;
			func_written = handle_conversion(*str, ap);
		}
		if (func_written == -1)
			return (-1);
		count += func_written;
		str++;
	}
	return (va_end(ap), count);
}

static int	handle_conversion(char fmt, va_list ap)
{
	int	written;

	written = -1;
	if (fmt == 'c')
		written = writeout_char(ap);
	else if (fmt == 's')
		written = writeout_string(ap);
	else if (fmt == 'p')
		written = writeout_pointer(ap, "0123456789abcdef");
	else if (fmt == 'd' || fmt == 'i')
		written = writeout_int(ap);
	else if (fmt == 'u')
		written = writeout_uint(ap);
	else if (fmt == 'x')
		written = writeout_hex(ap, "0123456789abcdef");
	else if (fmt == 'X')
		written = writeout_hex(ap, "0123456789ABCDEF");
	else if (fmt == '%')
	{
		written = write(1, "%", 1);
		if (written != -1)
			return (1);
	}
	return (written);
}
