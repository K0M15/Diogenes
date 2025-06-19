/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:32:13 by afelger           #+#    #+#             */
/*   Updated: 2025/06/19 15:29:26 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_forks(int has_forks[2], t_philosopher *phil)
{
	while (check_running(phil->state))
	{
		has_forks[0] = pthread_mutex_lock(&phil->forks[0]->locked) == 0;
		has_forks[1] = pthread_mutex_lock(&phil->forks[1]->locked) == 0;
		if (has_forks[0] && has_forks[1])
			return ;
		else
		{
			if (has_forks[0])
				pthread_mutex_unlock(&phil->forks[0]->locked);
			if (has_forks[1])
				pthread_mutex_unlock(&phil->forks[1]->locked);
		}
		usleep(1);
	}
}

int	get_forks(t_philosopher *phil)
{
	int	has_forks[2];

	has_forks[0] = 0;
	has_forks[1] = 0;
	lock_forks(has_forks, phil);
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
	ft_mutex_unlock(phil->forks[0]);
	ft_mutex_unlock(phil->forks[1]);
}

void	philo_main(t_philosopher *phil)
{
	bool	first_time;

	first_time = true;
	while (check_running(phil->state))
	{
		if (first_time && phil->id % 2)
			ft_sleep((phil->state->time_to_eat) / 2, phil->state);
		add_message(BLUE, PHIL_THINK, phil->id, phil->handle_speak);
		if (get_forks(phil))
			return ;
		ft_mutex_setvalue(&(phil->last_ate), ft_gettime());
		add_message(GREEN, PHIL_EAT, phil->id, phil->handle_speak);
		ft_sleep(phil->state->time_to_eat, phil->state);
		ft_mutex_incvalue(&(phil->has_eaten));
		drop_forks(phil);
		if (!check_running(phil->state))
			return ;
		add_message(BLUE, PHIL_SLEEP, phil->id, phil->handle_speak);
		ft_sleep(phil->state->time_to_sleep, phil->state);
		first_time = false;
	}
}

void	*philo_thread(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philo_main(philo);
	return (NULL);
}
