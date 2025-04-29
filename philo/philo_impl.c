/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_impl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:11 by afelger           #+#    #+#             */
/*   Updated: 2025/04/29 17:47:14 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	pickup_forks(t_philosopher *phil, t_appstate *state)
{
	uint32_t picked;

	picked = 0;
	// maybe return state?? to check for running state and maybe exit
	while (picked < 2)
	{
		if (!check_running(phil->state) && get_fork(&(state->forks[phil->id]), phil))
		{
			pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
			ft_printf(INFO_COLOR"%d %d has taken a fork\n"RES_COLOR, ft_get_ms(), phil->id);
			pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
			picked++;
		}
		else
			drop_forks(phil);
		if (!check_running(phil->state) && get_fork(&(state->forks[(phil->id + 1) % state->number_of_philosophers]), phil))
		{
			pthread_mutex_lock(&((t_appstate *) phil->state)->mut_write);
			ft_printf(INFO_COLOR"%d %d has taken a fork\n"RES_COLOR, ft_get_ms(), (phil->id + 1) % state->number_of_philosophers);
			pthread_mutex_unlock(&((t_appstate *) phil->state)->mut_write);
			picked++;
		}
		else
			drop_forks(phil);
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
}

void ft_sleep(int ms)
{
	uint64_t	end_time;
	uint64_t	buffer;

	buffer = ft_get_acc_us();
	end_time = buffer + ms * 1000;
	while (buffer < end_time)
	{
		if (end_time - buffer < 1000)
			usleep(300);
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
	while (phil->amount_eaten < state->each_must_eat) // && check_running(state))
	{
		ft_log("is thinking", phil);
		pickup_forks(phil, state);
		ft_log("is eating", phil);
		drop_forks(phil);
		ft_sleep(state->time_to_eat);
		ft_log("is sleeping", phil);
		ft_sleep(state->time_to_sleep);
		phil->amount_eaten++;
	}
	set_stop(state);
	ft_log("LEAVING", phil); // Debug
	return (NULL);
}