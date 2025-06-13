/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:32:13 by afelger           #+#    #+#             */
/*   Updated: 2025/06/12 14:51:41 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_forks(t_philosopher *phil){
	int has_forks[2];

	has_forks[0] = 0;
	has_forks[1] = 0;
	while (check_running(phil->state))
	{
		has_forks[0] = pthread_mutex_lock(&phil->forks[0]->locked) == 0;
		has_forks[1] = pthread_mutex_lock(&phil->forks[1]->locked) == 0;
		if (has_forks[0] && has_forks[1])
			break;
		else
		{
			if (has_forks[0])
				pthread_mutex_unlock(&phil->forks[0]->locked);
			if (has_forks[1])
				pthread_mutex_unlock(&phil->forks[1]->locked);
		}
		usleep(1);
	}
	if (check_running(phil->state) == false)
	{
		if (has_forks[0])
			pthread_mutex_unlock(&phil->forks[0]->locked);
		if (has_forks[1])
			pthread_mutex_unlock(&phil->forks[1]->locked);
		return (1);
	}
	add_message(BLUE, PHIL_FORK, phil->id, phil->handle_speak);
	add_message(BLUE, PHIL_FORK, phil->id, phil->handle_speak);
	return (0);
}


void	drop_forks(t_philosopher *phil)
{
	// rework this to know if this thread holds the forks
	ft_mutex_unlock(phil->forks[0]);
	ft_mutex_unlock(phil->forks[1]);
}

void	philo_main(t_philosopher *phil)
{
	bool firstTime;
	
	firstTime = true;
	while (check_running(phil->state)){
		if (firstTime && phil->id%2)
			ft_sleep((phil->state->time_to_eat) / 2, phil->state); // CHECK if first time
		add_message(BLUE, PHIL_THINK, phil->id, phil->handle_speak);
		if (get_forks(phil))
			return ;
		ft_mutex_setvalue(&(phil->last_ate), ft_gettime());
		add_message(GREEN, PHIL_EAT, phil->id, phil->handle_speak);
		ft_sleep(phil->state->time_to_eat, phil->state);	// could reduce time to account for last_ate time
		ft_mutex_incvalue(&(phil->has_eaten));
		drop_forks(phil);
		if (!check_running(phil->state))
			return ;
		add_message(BLUE, PHIL_SLEEP, phil->id, phil->handle_speak);
		ft_sleep(phil->state->time_to_sleep, phil->state);
		firstTime = false;
	}
}

void	*philo_thread(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    philo_main(philo);
    return NULL;
}
