/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:56 by afelger           #+#    #+#             */
/*   Updated: 2025/04/23 15:09:13 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void set_stop(t_appstate *state)
{
	pthread_mutex_lock(&state->mut_is_stopped);
	state->is_stopped = TRUE;
	pthread_mutex_unlock(&state->mut_is_stopped);
}

int check_philo(t_philosopher *phil)
{
	//test!
	(void) phil;
	sleep(10);
	return (1);
}

void *obs_main(void *args)
{
	int philo_id;
	t_appstate *state;
	boolean_t running;

	state = (t_appstate *)args;
	philo_id = 0;
	running = TRUE;
	while (running)
	{
		if (check_philo(&(state->philos[philo_id
			% state->number_of_philosophers])))
		{
			set_stop(state);
			running = FALSE;
		}
		else
		{
			philo_id++;
			usleep(10);
		}
	}
	return (NULL);
}

int	init_observer(pthread_t *observer, t_appstate *state)
{
	if (pthread_create(observer, NULL, obs_main, state))
		return (1);
	return (0);
}