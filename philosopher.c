/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:32:13 by afelger           #+#    #+#             */
/*   Updated: 2025/06/06 08:59:15 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks(t_philosopher *phil){
	while (check_running(phil->state))
	{
		if (!ft_mutex_lock(phil->forks[0]) || !ft_mutex_lock(phil->forks[1]))
			drop_forks(phil);
		else
			break;
		usleep(300);
	}
	add_message(BLUE, PHIL_FORK, phil->id, phil->handle_speak);
	add_message(BLUE, PHIL_FORK, phil->id, phil->handle_speak);
}


void	drop_forks(t_philosopher *phil)
{
	ft_mutex_unlock(phil->forks[0]);
	ft_mutex_unlock(phil->forks[1]);
}

void	philo_main(t_philosopher *phil)
{
	uint64_t	time;

	time = 0;
	while (check_running(phil->state)){
		add_message(BLUE, PHIL_THINK, phil->id, phil->handle_speak);
		ft_sleep((phil->state->time_to_die - phil->state->time_to_sleep
			- phil->state->time_to_eat) * 0.9, phil->state); // CHECK if first time
		get_forks(phil);
		time = ft_gettime();
		add_message(GREEN, PHIL_EAT, phil->id, phil->handle_speak);
		ft_mutex_setvalue(&(phil->last_ate), time);
		ft_mutex_incvalue(&(phil->has_eaten));
		drop_forks(phil);
		ft_sleep(time += phil->state->time_to_eat, phil->state);
		add_message(BLUE, PHIL_SLEEP, phil->id, phil->handle_speak);
		ft_sleep(time += phil->state->time_to_sleep, phil->state);
	}
}

void	*philo_thread(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    philo_main(philo);
    return NULL;
}
