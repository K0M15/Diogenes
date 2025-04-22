/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:32:31 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 07:58:30 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	get_divisor(unsigned int n);
static int			handle_negative(long long *data, int *count);

int	writeout_uint(va_list ap)
{
	unsigned int	number;
	int				count;
	unsigned int	divisor;
	char			result;

	number = va_arg(ap, unsigned int);
	count = 0;
	divisor = get_divisor(number);
	if (divisor == 0)
		if (write(ft_printf_get_fd(), "0", 1) == -1)
			return (-1);
	if (divisor == 0)
		return (1);
	while (divisor != 0)
	{
		result = number / divisor + '0';
		if (write(ft_printf_get_fd(), &result, 1) == -1)
			return (-1);
		number = number - number / divisor * divisor;
		divisor /= 10;
		count++;
	}
	return (count);
}

int	writeout_int(va_list ap)
{
	long long	divisor;
	char		result;
	long long	data;
	int			count;

	count = 0;
	data = va_arg(ap, int);
	if (handle_negative(&data, &count) == -1)
		return (-1);
	divisor = get_divisor(data);
	if (divisor == 0)
		if (write(ft_printf_get_fd(), "0", 1) == -1)
			return (-1);
	if (divisor == 0)
		return (1);
	while (divisor != 0)
	{
		result = data / divisor + '0';
		data = data - data / divisor * divisor;
		if (write(ft_printf_get_fd(), &result, 1) == -1)
			return (-1);
		divisor /= 10;
		count++;
	}
	return (count);
}

static unsigned int	get_divisor(unsigned int n)
{
	long long	div;

	if (n == 0)
		return (0);
	div = 10000000000;
	while (n / div == 0)
		div /= 10;
	return (div);
}

static int	handle_negative(long long *data, int *count)
{
	if (*data < 0)
	{
		(*data) *= -1;
		(*count)++;
		if (write(ft_printf_get_fd(), "-", 1) == -1)
			return (-1);
	}
	return (1);
}
