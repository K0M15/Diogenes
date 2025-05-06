/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_impl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:11 by afelger           #+#    #+#             */
/*   Updated: 2025/05/06 14:36:40 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	pickup_forks(t_philosopher *phil, t_appstate *state)
{
	uint32_t picked;

	picked = (phil->forks[0] != NULL) + (phil->forks[1] != NULL);
	// maybe return state?? to check for running state and maybe exit
	while (picked < 2)
	{
		if (check_running(phil->state) && phil->forks[0] == NULL && get_fork(&(state->forks[phil->id]), phil))
		{
			// ft_log("%d %d has taken a fork",phil);
			ft_log2("has taken a fork 0", phil);
			picked++;
		}
		if (check_running(phil->state) && get_fork(&(state->forks[(phil->id + 1) % state->number_of_philosophers]), phil))
		{
			// ft_log("has taken a fork", phil);
			ft_log2("has taken a fork 1", phil);
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
		ft_printf(INFO_COLOR"%d %d %s\n"RES_COLOR, time, phil->id, msg);
		pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
	}
	else
	{
		pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
		ft_printf(INFO_COLOR2"%d %d %s - out of scope\n"RES_COLOR, time, phil->id, msg);
		pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
	}
}

void	ft_log2(char *msg, t_philosopher *phil)
{
	uint32_t time;

	time = ft_get_ms();
	if (check_running(phil->state))
	{
		pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
		ft_printf(INFO_COLOR2"%d %d %s\n"RES_COLOR, time, phil->id, msg);
		pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
	}
	else
	{
		pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
		ft_printf(INFO_COLOR2"%d %d %s - out of scope\n"RES_COLOR, time, phil->id, msg);
		pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
	}
}

void ft_sleep(int ms)
{
	uint64_t	end_time;
	uint64_t	buffer;

	buffer = ft_get_acc_us();
	end_time = buffer + ms * 1000;
	while (buffer <= end_time)
	{
		if (end_time - buffer < 1000)
			usleep(100);
		else
			usleep(700);
		buffer = ft_get_acc_us();
	}
	return ;
}

void	*phil_main(void *obj)
{
	t_philosopher	*phil;
	t_appstate		*state;

	phil = (t_philosopher *) obj;
	state = (t_appstate *) phil->state;
	while ((state->each_must_eat == 0
		|| phil->amount_eaten < state->each_must_eat)
		&& check_running(state))
	{
		ft_log("is thinking", phil);
		pickup_forks(phil, state);
		ft_log("is eating", phil);
		phil->ate_last = ft_get_ms();
		ft_sleep(state->time_to_eat);
		drop_forks(phil);
		phil->amount_eaten++;
		ft_log("is sleeping", phil);
		ft_sleep(state->time_to_sleep);
	}
	ft_log("LEAVING", phil); // Debug
	return (NULL);
}
