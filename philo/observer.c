/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:56 by afelger           #+#    #+#             */
/*   Updated: 2025/05/07 13:19:35 by afelger          ###   ########.fr       */
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

int check_philo(t_philosopher *phil, t_appstate *state)
{
	
	if (phil->ate_last + state->time_to_die < ft_get_ms())
	{
		ft_log("died", phil);
		pthread_mutex_lock(&state->mut_write);
		ft_printf(ERR_COLOR"%d died ate last at %u\n"RES_COLOR, phil->id, phil->ate_last);
		pthread_mutex_unlock(&state->mut_write);
		return (1);
	}
	return (0);
}

int check_all_eaten(t_appstate *state)
{
	uint32_t have_not_eaten;
	uint32_t i;

	have_not_eaten = state->number_of_philosophers;
	if (state->each_must_eat == 0)
		return (0);
	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (state->philos[i].amount_eaten >= state->each_must_eat)
			have_not_eaten--;
		i++;
		usleep(100);
	}
	return (have_not_eaten == 0);
}

void *obs_main(void *args)
{
	uint32_t philo_id;
	t_appstate *state;

	state = (t_appstate *)args;
	ft_sleep(state->time_to_die / 2, state); // if ttd > 50 then underflow
	while (check_running(state))
	{
		philo_id = 0;
		while (philo_id < state->number_of_philosophers && check_running(state))
		{
			if (check_philo(&(state->philos[philo_id]), state))
				set_stop(state);
			philo_id++;
		}
		usleep(2000);
		if (check_running(state) && check_all_eaten(state))
			set_stop(state);
		usleep(5000); //OPTIMIZE
	}
	return (NULL);
}

int	init_observer(pthread_t *observer, t_appstate *state)
{
	if (pthread_create(observer, NULL, obs_main, state))
		return (1);
	return (0);
}