/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:32:23 by afelger           #+#    #+#             */
/*   Updated: 2025/06/19 15:47:17 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_mutex_lock(t_ft_mutex *mut)
{
	bool	result;

	result = false;
	if (pthread_mutex_lock(&(mut->checklock)))
		return (ft_error(MUTEX_LOCK_ERR, NULL), result);
	if (mut->value == false)
	{
		result = true;
		mut->value = true;
		if (pthread_mutex_lock(&(mut->locked)))
			return (pthread_mutex_unlock(&(mut->checklock)),
				ft_error(MUTEX_LOCK_ERR, NULL), result);
	}
	return (pthread_mutex_unlock(&(mut->checklock)), result);
}

void	ft_mutex_unlock(t_ft_mutex *mut)
{
	pthread_mutex_lock(&(mut->checklock));
	pthread_mutex_unlock(&(mut->locked));
	mut->value = false;
	pthread_mutex_unlock(&(mut->checklock));
}

bool	ft_mutex_setvalue(t_ft_mutex *mut, uint64_t value)
{
	if (pthread_mutex_lock(&(mut->checklock)))
		return (ft_error(MUTEX_LOCK_ERR, NULL), false);
	mut->value = value;
	pthread_mutex_unlock(&(mut->checklock));
	return (true);
}

bool	ft_mutex_incvalue(t_ft_mutex *mut)
{
	if (pthread_mutex_lock(&(mut->checklock)))
		return (ft_error(MUTEX_LOCK_ERR, NULL), false);
	mut->value++;
	pthread_mutex_unlock(&(mut->checklock));
	return (true);
}

uint64_t	ft_mutex_getvalue(t_ft_mutex *mut)
{
	uint64_t	result;

	pthread_mutex_lock(&(mut->checklock));
	pthread_mutex_lock(&(mut->locked));
	result = mut->value;
	pthread_mutex_unlock(&(mut->locked));
	pthread_mutex_unlock(&(mut->checklock));
	return (result);
}
