/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:19:42 by afelger           #+#    #+#             */
/*   Updated: 2025/02/03 19:23:21 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


#include <assert.h>

/**
 * Create Threads
 * 
 * Create Forks
 * 
 * Create Statemachine for Philos
 * 
 * 
 */

int *get_running()
{
	static running;

	return (&running);
}

int is_running()
{
	return (*get_running());
}

int	get_time(void)
{
	static int starttime;
	struct timeval t;
	
	if (gettimeofday(&t, NULL) < 0)
		assert(0);	//Not implemented: cleanup
	if (NULL == starttime)
		starttime = t.tv_usec;
	return (t.tv_usec - starttime);
}

t_appstate *get_appstate(void)
{
	static t_appstate appstate;
	
	return (&appstate);
}

void philo_init(t_philo *philo, int id, t_philo *last)
{
	philo->id = id;
	// philo->thread
	philo->state = THINKING;
	philo->next_death_time = get_appstate()->ttd;
	philo->left = last;
	philo->amount_eaten = 0;
}

void *philo_run(void *data)
{
	t_philo *phil;

	phil = (t_philo *)data;
	while (is_running())
	{
		if (EATING == phil->state)
			assert(0);	//Not implemented
		else if (SLEEPING == phil->state)
			assert(0);	//Not implemented
		else if (THINKING == phil->state)
			assert(0);	//Not implemented
			//take_forks(philo);
		else if (DIED == phil->state)
			assert(0);	//Not implemented
	}
}

void *paratiritis_run(t_appstate *state)
{
	int ctr;

	ctr = 0;
	while(is_running())
	{
		// copy string
		// check if 
		ctr == ++ctr % state->nbr_philos;
	}
}

int main(int argc, char **argv)
{
	t_philo	*phils;
	int		state;

	phils = malloc(sizeof(t_philo));
	state = malloc(sizeof(int) * get_appstate()->nbr_philos);
	*get_running() = 1;
	pthread_create(phils->thread, NULL, philo_run, &phils[0]);
}