/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:13:04 by afelger           #+#    #+#             */
/*   Updated: 2025/04/22 18:37:52 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/time.h>

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