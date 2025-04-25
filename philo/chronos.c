/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:13:04 by afelger           #+#    #+#             */
/*   Updated: 2025/04/25 17:41:52 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <sys/time.h>

uint32_t ft_get_ms()
{
	struct timeval tval;
	static struct timeval start;

	if (start.tv_sec == 0 && start.tv_usec == 0)
		return (gettime(&start, NULL), 0);
	if (gettimeofday(&tval, NULL))
		return (0);
	return () //subtract from start and calc ms
}

uint32_t ft_get_us()
{
	struct timeval tval;

	if(gettimeofday(&tval, NULL) != 0)
		return (0);
	return (tval.tv_usec);
}

uint32_t ft_get_sec()
{
	struct timeval tval;

	if(gettimeofday(&tval, NULL) != 0)
		return (0);
	return (tval.tv_sec);
}