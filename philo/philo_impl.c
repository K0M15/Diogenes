/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_impl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:11 by afelger           #+#    #+#             */
/*   Updated: 2025/04/25 19:45:53 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	pickup_forks(t_philosopher *phil, t_appstate *state)
{
	uint32_t picked;

	picked = 0;
	while (picked < 2)
	{
		if (check_running(phil->state) && get_fork(&(state->forks[phil->id]), phil))
		{
			pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
			ft_printf(INFO_COLOR"Picked up fork %d\n"RES_COLOR, phil->id);
			pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
			picked++;
		}
		if (check_running(phil->state) && get_fork(&(state->forks[(phil->id + 1) % state->number_of_philosophers]), phil))
		{
			pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
			ft_printf(INFO_COLOR"Picked up fork %d\n"RES_COLOR, (phil->id + 1) % state->number_of_philosophers);
			pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
			picked++;
		}
		usleep(1);
	}
}

void	ft_log(char *msg, t_philosopher *phil)
{
	uint32_t time;

	time = ft_get_ms();
	if (check_running(phil->state))
	{
		pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
		ft_printf(INFO_COLOR"%d > Philosopher %d %s\n"RES_COLOR, time, phil->id, msg);
		pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
	}
}

void	*phil_main(void *obj)
{
	t_philosopher	*phil;
	t_appstate		*state;

	phil = (t_philosopher *) obj;
	state = (t_appstate *) phil->state;
	while (phil->amount_eaten < state->each_must_eat && check_running(state))
	{
		ft_log("SLEEPING", phil);
		usleep(state->time_to_sleep * 1000);
		ft_log("THINKING", phil);
		pickup_forks(phil, state);
		ft_log("EATING", phil);
		drop_forks(phil);
		usleep(state->time_to_eat * 1000);
		phil->amount_eaten++;
	}
	set_stop(state);
	ft_log("LEAVING", phil);
	return (NULL);
}