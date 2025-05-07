/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_impl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:11 by afelger           #+#    #+#             */
/*   Updated: 2025/05/07 15:34:56 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	pickup_forks(t_philosopher *phil, t_appstate *state)
{
	uint32_t picked;

	picked = (phil->forks[0] != NULL) + (phil->forks[1] != NULL);
	// ft_log2("is getting forks", phil);
	while (picked < 2 && check_running(state))
	{
		// add a way to check if the forks should stay in hand to prevent dropping in case of not getting the other fork
		if (check_running(phil->state) 
			&& get_fork(&(state->forks[phil->id]), phil))
			// && get_fork(&(state->forks[((phil->id % 2) + phil->id) % state->number_of_philosophers]), phil))
		{
			int forkNo = phil->id;
			pthread_mutex_lock(&state->mut_write);
			ft_printf("%d %d has taken fork %d\n", ft_get_ms(), phil->id, forkNo);
			pthread_mutex_unlock(&state->mut_write);
			// ft_log("has taken a fork",phil);
			picked++;
		}
		else
			drop_forks(phil);
		if (check_running(phil->state) 
			&& get_fork(&(state->forks[(phil->id + 1) % state->number_of_philosophers]), phil))
		{
			int forkNo = (phil->id + 1) % state->number_of_philosophers;
			pthread_mutex_lock(&state->mut_write);
			ft_printf("%d %d has taken fork %d\n", ft_get_ms(), phil->id, forkNo);
			pthread_mutex_unlock(&state->mut_write);
			// ft_log("has taken a fork " , phil);
			picked++;
		}
		else
			drop_forks(phil);
		usleep(500);
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

void	ft_sleep(int ms, t_appstate *state)
{
	uint64_t	target;
	uint64_t	now;

	(void)state;
	target = ft_get_acc_us() + (uint64_t)(ms * 1000);
	while (1)
	{
		now = ft_get_acc_us();
		if (now >= target)
			break;
		if (now >= target - 2000)
			usleep(100); // last 1ms: short sleep
		else
			usleep(1000); // safe longer sleep
	}
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
		phil->ate_last = ft_get_ms();
		ft_log("is eating", phil);
		ft_sleep(state->time_to_eat, state);
		drop_forks(phil);
		phil->amount_eaten++;
		ft_log("is sleeping", phil);
		ft_sleep(state->time_to_sleep, state);
	}
	ft_log("LEAVING", phil); // Debug
	return (NULL);
}
