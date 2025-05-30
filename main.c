/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:14:16 by afelger           #+#    #+#             */
/*   Updated: 2025/05/30 14:31:29 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t ft_gettime()
{
	static uint64_t			start;
	static struct timeval	current;
	if (start == 0)
	{
		if(gettimeofday(&current, NULL))
			ft_error(RETRIEVE_TIME_ERR);
		else
			start = (current.tv_sec + current.tv_usec / 10);
			return (0);
	}
	if (gettimeofday(&current, NULL))
		ft_error(RETRIEVE_TIME_ERR);
	return ((current.tv_sec + current.tv_usec / 10) - start);
}

void ft_sleep(int ms)
{
	uint64_t start;
	uint64_t curr;

	start = ft_gettime();
	curr = start;
	while(start + ms > curr)
	{
		curr = ft_gettime();
		usleep((((start + ms * 10) - curr) / 2) * 100);
	}
}

void ft_error(enum e_messagetxt msg)
{
	add_message(RED,msg, ft_gettime() / 10, UINT32_MAX);
}

int	createPhilosphers(t_appstate *state)
{
	uint8_t	i;

	i = 0;
	while(i <= state->number_philos)
	{
		state->philosopher[i].id = i + 1;
		state->philosopher[i].handle_speak = &state->speaker;
		state->philosopher[i].state = state;
		if (create_ft_mutex(&(state->philosopher[i].has_eaten))
			|| create_ft_mutex(&(state->philosopher[i].last_ate)))
		{
			state->number_philos = i;	// on error this will not delete all the forks
			deletePhilosophers(state);	
			return (1);
		}
		state->philosopher[i].forks[0] = &state->fork[i];
		state->philosopher[i].forks[1] = &state->fork[i + 1 % state->number_philos];
		i++;
	}
	i = 0;
	while (i < state->number_philos)
		if (pthread_create(&(state->philosopher[i]), NULL, philo_main, state))
			return (1);
	return (0);
}

void	deletePhilosophers(t_appstate *state)
{
	int16_t	i;

	i = state->number_philos ;
	while (i > -1)
	{
		destroy_ft_mutex(&(state->philosopher[i].has_eaten));
		destroy_ft_mutex(&(state->philosopher[i].last_ate));
		i--;
	}
}

int	createForks(t_appstate *state)
{
	uint8_t	i;

	i = 0;
	while (i < 200)
	{
		if (create_ft_mutex(&(state->fork[i])))
			return (1);
		i++;
	}
	return (0);
}

void deleteForks(t_appstate *state)
{
	uint8_t	i;

	i = 0;
	while (i < 200)
	{
		destroy_ft_mutex(&(state->fork[i]));
	}
	return (0);
}


int	main()
{
	t_appstate state;
	//sizeof(t_appstate);		// stay under 32kb
	
	ft_gettime();			//Prime start
	
}