/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:32:13 by afelger           #+#    #+#             */
/*   Updated: 2025/05/20 15:30:39 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks(t_philosopher *phil){
	uint8_t		*forks;
	uint64_t	time;

	forks = phil->forks;
	while (check_running(phil->state) && forks[0] != UINT8_MAX && forks[1] != UINT8_MAX)
	{
		if (ft_mutex_lock(phil->id - 1))
			forks[0] = phil->id - 1;
		if (ft_mutex_lock(phil->id))
			forks[1] = phil->id;
		if (forks[0] == UINT8_MAX || forks[1] == UINT8_MAX)
			drop_forks(phil);
		usleep(300);
	}
	time = ft_gettime();
	add_message(BLUE, PHIL_FORK, time, phil->id);
	add_message(BLUE, PHIL_FORK, time, phil->id);
}

void	drop_forks(t_philosopher *phil)
{
	ft_mutex_unlock(phil->id - 1);
	ft_mutex_unlock(phil->id);
}

void	philo_main(t_philosopher *phil)
{
	uint64_t	time;

	time = 0;
	while (check_running(phil->state)){
		add_message(BLUE, PHIL_THINK, time, phil->id);
		get_forks(phil);
		time = ft_gettime();
		add_message(GREEN, PHIL_EAT, time, phil->id);
		ft_mutex_setvalue(&(phil->last_ate), time);
		ft_mutex_incvalue(&(phil->has_eaten));
		drop_forks(phil);
		ft_sleep(time += phil->state->time_to_eat);
		add_message(BLUE, PHIL_SLEEP, time, phil->id);
		ft_sleep(time += phil->state->time_to_sleep);
	}
}
