/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:24:05 by afelger           #+#    #+#             */
/*   Updated: 2025/06/19 15:24:40 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint32_t	create_ft_mutex(t_ft_mutex *mut)
{
	mut->value = false;
	return (pthread_mutex_init(&(mut->checklock), NULL)
		|| pthread_mutex_init(&(mut->locked), NULL));
}

uint32_t	destroy_ft_mutex(t_ft_mutex *mut)
{
	return (pthread_mutex_destroy(&(mut->checklock))
		|| pthread_mutex_init(&(mut->locked), NULL));
}
