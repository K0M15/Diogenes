/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:56 by afelger           #+#    #+#             */
/*   Updated: 2025/05/06 14:33:17 by afelger          ###   ########.fr       */
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

int check_philo(t_philosopher *phil, t_appstate *state, uint32_t time)
{
	
	if (phil->ate_last + state->time_to_die < time)
	{
		ft_log("died", phil);
		return (1);
	}
	return (0);
}

int check_all_eaten(t_appstate *state)
{
	uint32_t have_not_eaten;
	uint32_t i;

	have_not_eaten = state->number_of_philosophers;
	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (state->philos[i].amount_eaten >= state->each_must_eat)
			have_not_eaten--;
		i++;
	}
	return (have_not_eaten == 0);
}

void *obs_main(void *args)
{
	int philo_id;
	t_appstate *state;
	uint32_t time;

	state = (t_appstate *)args;
	ft_sleep(state->time_to_die - 50);
	philo_id = 0;
	while (check_running(state))
	{
		time = ft_get_ms();
		if (check_philo(&(state->philos[philo_id
			% state->number_of_philosophers]), state, time))
			set_stop(state);
		else
			philo_id++;
		if (check_running(state) && check_all_eaten(state))
			set_stop(state);
		// usleep(1);
	}
	return (NULL);
}

int	init_observer(pthread_t *observer, t_appstate *state)
{
	if (pthread_create(observer, NULL, obs_main, state))
		return (1);
	return (0);
}