/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:31:40 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 07:58:41 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	writeout_hex(va_list ap, const char *hex_string)
{
	unsigned int	number;
	int				count;
	int				shift[2];
	unsigned int	buff;

	count = 0;
	shift[0] = 0x7;
	shift[1] = 0;
	number = va_arg(ap, unsigned int);
	while (shift[0] + 1)
	{
		buff = (number & (0xf << (shift[0] * 4))) >> (shift[0] * 4);
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
