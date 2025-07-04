/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:14:16 by afelger           #+#    #+#             */
/*   Updated: 2025/06/25 10:43:22 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

bool	init_state(t_appstate *state)
{
	uint32_t	ctr;

	state->philosophers = malloc(sizeof(t_philosopher) * state->number_philos);
	state->forks = malloc(sizeof(t_ft_mutex) * state->number_philos);
	if (state->forks == NULL || state->philosophers == NULL)
		return (1);
	ctr = 0;
	while (ctr < state->number_philos)
	{
		state->philosophers[ctr].state = state;
		if (create_ft_mutex(&(state->philosophers[ctr].last_ate))
			|| create_ft_mutex(&(state->philosophers[ctr].has_eaten))
			|| create_ft_mutex(&(state->forks[ctr])))
			return (1);
		state->philosophers[ctr].forks[0] = &(state->forks[ctr]);
		state->philosophers[ctr].forks[1] = &(state->forks[(ctr + 1)
				% state->number_philos]);
		state->philosophers[ctr].handle_speak = &(state->speaker);
		state->philosophers[ctr].id = ctr + 1;
		ctr++;
	}
	create_ft_mutex(&(state->running));
	ft_mutex_setvalue(&(state->running), true);
	return (0);
}

bool	start_threads(t_appstate *state)
{
	uint32_t	ctr;

	ctr = 0;
	if (init_speaker(&(state->speaker), state))
		return (1);
	while (ctr < state->number_philos)
	{
		if (pthread_create(&(state->philosophers[ctr].thread), NULL,
				philo_thread, &(state->philosophers[ctr])))
			return (1);
		ctr++;
	}
	if (pthread_create(&(state->observer), NULL, observer_wrapper, state))
		return (1);
	return (0);
}

void	cleanup(t_appstate *state)
{
	uint32_t	ctr;

	ctr = 0;
	while (ctr < state->number_philos)
		pthread_join(state->philosophers[ctr++].thread, NULL);
	pthread_join(state->speaker.thread, NULL);
	ctr = 0;
	pthread_mutex_destroy(&(state->speaker.lock_write));
	while (ctr < state->number_philos)
	{
		destroy_ft_mutex(&(state->philosophers[ctr].has_eaten));
		destroy_ft_mutex(&(state->philosophers[ctr].last_ate));
		destroy_ft_mutex(&(state->forks[ctr++]));
	}
	free(state->philosophers);
	free(state->forks);
	destroy_ft_mutex(&(state->running));
}

int	main(int argc, char **argv)
{
	t_appstate	state;

	if (parse_input(argc, argv, &state))
		return (display_usage(), 1);
	else
	{
		ft_gettime();
		if (init_state(&state))
			return ((void)!write(2, MSG_STATE_INIT_ERR,
				sizeof(MSG_STATE_INIT_ERR)), 1);
		ft_error(NO_MESSAGE, &state.speaker);
		if (start_threads(&state))
			return ((void)!write(2, MSG_START_THREADS_ERR,
				sizeof(MSG_START_THREADS_ERR)), 1);
		pthread_join(state.observer, NULL);
		cleanup(&state);
	}
	return (0);
}
