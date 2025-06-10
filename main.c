/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:14:16 by afelger           #+#    #+#             */
/*   Updated: 2025/06/10 12:49:23 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

uint64_t ft_gettime()
{
	static uint64_t	start;
	struct timeval	current;
	if (start == 0)
	{
		if(gettimeofday(&current, NULL))
			ft_error(RETRIEVE_TIME_ERR);
		else
		{
			start = current.tv_sec * 1000 + (current.tv_usec / 1000);
			return (0);
		}
	}
	if (gettimeofday(&current, NULL))
		ft_error(RETRIEVE_TIME_ERR);
	return (current.tv_sec * 1000 + (current.tv_usec / 1000) - start);
}

void ft_sleep(int ms, t_appstate *state)
{
	uint64_t start;
	uint64_t curr;

	start = ft_gettime();
	curr = start;
	while(start + ms > curr && check_running(state))
	{
		curr = ft_gettime();
		usleep((((start + ms * 10) - curr) / 2) * 100);
	}
}

void ft_error(enum e_messagetxt msg)
{
	// add_message(RED,msg, UINT32_MAX, );
	(void) msg; // Placeholder for actual message handling
	printf("ERROR");
}

static void	displayUsage()
{
	printf("usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
}

static bool initState(t_appstate *state)
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
		if (create_ft_mutex(&(state->philosophers[ctr].last_ate)) ||
			create_ft_mutex(&(state->philosophers[ctr].has_eaten)) ||
			create_ft_mutex(&(state->forks[ctr])))
			return (1);
		state->philosophers[ctr].forks[0] = &(state->forks[ctr]);
		state->philosophers[ctr].forks[1] = &(state->forks[ctr+1%state->number_philos]);
		state->philosophers[ctr].handle_speak = &(state->speaker);
		state->philosophers[ctr].id = ctr + 1;
		ctr++;
	}
	create_ft_mutex(&(state->running));
	ft_mutex_setvalue(&(state->running), true);
	return (0);
}

static bool	startThreads(t_appstate *state)
{
	uint32_t ctr;

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
	uint32_t ctr;

	ctr = 0;
	while (ctr < state->number_philos)
		pthread_join(state->philosophers[ctr++].thread, NULL);
	pthread_join(state->speaker.thread, NULL);
	ctr = 0;
	free(state->speaker.read);
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

// int	main(int argc, char **argv)
// {
// 	t_appstate state;
	
// 	if(parse_input(argc, argv, &state))
// 		displayUsage();
// 	else
// 	{
// 		ft_gettime();			//Prime start
// 		initState(&state);
// 		startThreads(&state);
// 		pthread_join(state.observer, NULL);
// 		cleanup(&state);
// 	}
// }

// int main(int argc, char **argv)
// {
// 	t_appstate state;
// 	int i;

// 	i = 0;
	
// 	if(parse_input(argc, argv, &state))
// 		displayUsage();
// 	else
// 	{
// 		ft_gettime();			//Prime start
// 		initState(&state);
// 		init_speaker(&(state.speaker), &state);
// 		while (check_running(&state))
// 		{
// 			add_message(RED, PHIL_EAT, 10, &(state.speaker));
// 			usleep(3e6);
// 			pthread_mutex_lock(&(state.speaker.lock_write));
// 			printf("Write pos: %p\n", state.speaker.write);
// 			printf("Read pos: %p\n", state.speaker.read);
// 			pthread_mutex_unlock(&(state.speaker.lock_write));
// 			i++;
// 			if (i > 3)
// 				stop_running(&state);
// 		}
// 		pthread_join(state.speaker.thread, NULL);
// 		cleanup(&state);
// 		printf("Finished execution.\n");
// 	}
// }

int main ()
{
	t_appstate state;

	parse_input(5, (char *[]){"./philo", "2", "800", "200", "200"}, &state);
	ft_gettime(); // Prime start
	initState(&state);
	state.number_philos = 1;
	if (startThreads(&state))
	{
		displayUsage();
		ft_error(MEM_ERR);
		return (1);
	}
	pthread_join(state.observer, NULL);
	cleanup(&state);
	return (0);
}