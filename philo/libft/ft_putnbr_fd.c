/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:13:01 by afelger           #+#    #+#             */
/*   Updated: 2024/10/21 08:52:11 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static long	get_divisor(int n)
{
	long	div;

	div = 10000000000;
	while (n / div == 0)
		div /= 10;
	return (div);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	divisor;
	char	result;
	long	data;

	data = n;
	if (n == 0)
	{
		ft_putstr_fd("0", fd);
		return ;
	}
	divisor = get_divisor(data);
	if (data < 0)
	{
		data *= -1;
		ft_putchar_fd('-', fd);
	}
	while (divisor != 0)
	{
		result = data / divisor + '0';
		data = data - data / divisor * divisor;
		ft_putchar_fd(result, fd);
		divisor /= 10;
	}
}
