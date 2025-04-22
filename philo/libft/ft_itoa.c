/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:06:23 by afelger           #+#    #+#             */
/*   Updated: 2024/10/20 10:27:43 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	get_divisor(int n)
{
	long	div;

	div = 10000000000;
	while (n / div == 0)
		div /= 10;
	return (div);
}

static int	handle_zero(int n, char *result)
{
	if (n == 0)
	{
		result[0] = '0';
		return (1);
	}
	return (0);
}

static unsigned int	get_number_len(int n)
{
	unsigned int	r;
	unsigned int	div;

	r = 1;
	div = 1;
	if (n < 0)
	{
		n *= -1;
		r++;
	}
	while (n / div > 9)
	{
		r++;
		div *= 10;
	}
	return (r);
}

static void	loop(char *result, long *data, long *divisor, int *position)
{
	result[*position] = *data / *divisor + '0';
	*data = *data - *data / *divisor * *divisor;
	*divisor /= 10;
	(*position)++;
}

char	*ft_itoa(int n)
{
	long	divisor;
	char	*result;
	int		position;
	long	data;

	position = 0;
	data = n;
	result = ft_calloc(get_number_len(n) + 1, 1);
	if (!result)
		return (result);
	if (handle_zero(n, result))
		return (result);
	if (data < 0)
	{
		data *= -1;
		result[position++] = '-';
	}
	divisor = get_divisor(data);
	while (divisor != 0)
		loop(result, &data, &divisor, &position);
	return (result);
}

// #include <libc.h>

// int main()
// {
// 	printf("%s /",ft_itoa(0));
// 	// printf("%s /",ft_itoa(214748364778484));
// 	printf("%s\n",ft_itoa(-2147483648));
// }