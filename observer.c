/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:09:49 by afelger           #+#    #+#             */
/*   Updated: 2025/05/28 15:50:31 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_running(t_appstate *state)
{
	bool is_running;
	
	is_running = ft_mutex_getvalue(&(state->running));
	return (is_running);
}
bool 		stop_running(t_appstate *state)
{
	ft_mutex_setvalue(&(state->running), false);
	return (true);
}

int	check_philo(t_philosopher *phil, uint64_t time){
	if (ft_mutex_getvalue(&(phil->has_eaten)) + phil->state->time_to_die < time)
		stop_running(phil->state);
	if (ft_mutex_getvalue(&(phil->has_eaten)))
		return (1);
		//TODO....
	return (0);
}

void observer_main(t_appstate *state){
	uint8_t		has_eaten;
	uint8_t		check;
	uint64_t	time;

	while (check_running(state))
	{
		has_eaten = 0;
		check = 0;
		time = ft_gettime();
		while (++check < state->number_philos && check_running(state))
			has_eaten += check_philo(&(state->philosopher[check]), time);	//should be quite fast, if time error occ, recheck time each loop
		if (has_eaten == state->number_philos)
			stop_running(state);
	}
}
