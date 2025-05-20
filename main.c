/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:14:16 by afelger           #+#    #+#             */
/*   Updated: 2025/05/20 15:05:58 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t ft_gettime()
{
	static uint64_t			start;
	static struct timeval	current;
	if (start == 0)
	{
		if(gettimeofday(&current, NULL))
			d_error(RETRIEVE_TIME_ERR);
		else
			start = (current.tv_sec + current.tv_usec / 10);
			return (0);
	}
	if (gettimeofday(&current, NULL))
		d_error(RETRIEVE_TIME_ERR);
	return ((current.tv_sec + current.tv_usec / 10) - start);
}

void ft_sleep(int ms)
{
	uint64_t start;
	uint64_t curr;

	start = ft_gettime();
	curr = start;
	while(start + ms > curr)
	{
		curr = ft_gettime();
		usleep((((start + ms * 10) - curr) / 2) * 100);
	}
}

void ft_error(enum e_messagetxt msg)
{
	add_message(RED,msg, ft_gettime() / 10, UINT32_MAX);
}

int	main()
{
	sizeof(t_appstate);		// stay under 32kb
	ft_gettime();			//Prime start
	
}