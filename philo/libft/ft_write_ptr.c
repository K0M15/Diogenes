/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:30:36 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 07:58:00 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	writeout_pointer(va_list ap, const char *hex_string)
{
	unsigned long long	number;
	int					count;
	int					shift[2];
	unsigned long long	buff;

	count = 2;
	shift[0] = 0xf;
	shift[1] = 0;
	number = (unsigned long long) va_arg(ap, void *);
	if (write(ft_printf_get_fd(), "0x", 2) == -1)
		return (-1);
	while (shift[0] + 1)
	{
		buff = (number & (0xfL << (shift[0] * 4))) >> (shift[0] * 4);
		if (buff != 0 || (shift[0] == 0 && buff == 0) || shift[1] > 0)
		{
			shift[1] += (buff != 0);
			if (write(ft_printf_get_fd(), &hex_string[buff], 1) == -1)
				return (-1);
			count++;
		}
		shift[0]--;
	}
	return (count);
}
