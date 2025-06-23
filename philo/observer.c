/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:09:49 by afelger           #+#    #+#             */
/*   Updated: 2025/06/23 15:31:36 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_running(t_appstate *state)
{
	bool	is_running;

	is_running = ft_mutex_getvalue(&(state->running));
	return (is_running);
}

bool	stop_running(t_appstate *state)
{
	ft_mutex_setvalue(&(state->running), false);
	return (true);
}

int	check_philo(t_philosopher *phil, uint64_t time)
{
	if (phil->state->notepme
		&& ft_mutex_getvalue(&(phil->has_eaten)) >= phil->state->notepme)
		return (1);
	if (ft_mutex_getvalue(&(phil->last_ate)) + phil->state->time_to_die < time)
	{
		add_message(RED, PHIL_DIE, phil->id, phil->handle_speak);
		stop_running(phil->state);
	}
	return (0);
}

void	observer_main(t_appstate *state)
{
	uint8_t		has_eaten;
	uint8_t		check;

	while (check_running(state))
	{
		has_eaten = 0;
		check = 0;
		while (check < state->number_philos && check_running(state))
		{
			has_eaten += check_philo(&(state->philosophers[check]),
					ft_gettime());
			check++;
		}
		if (has_eaten == state->number_philos && state->notepme != 0)
			stop_running(state);
		usleep(1000);
	}
}

void	*observer_wrapper(void *arg)
{
	t_appstate	*state;

	state = (t_appstate *)arg;
	observer_main(state);
	return (NULL);
}
