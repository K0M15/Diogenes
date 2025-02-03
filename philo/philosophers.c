/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:19:42 by afelger           #+#    #+#             */
/*   Updated: 2025/02/03 19:58:10 by afelger          ###   ########.fr       */
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
	philo->state = THINKING;
	philo->next_death_time = get_appstate()->ttd;
	philo->left = last;
	philo->amount_eaten = 0;
	philo->next_sleep_time = 0;		// FINISH EATING
	philo->next_wake_time = 0;
}

void philo_set_state(t_philo *phil, t_philostate state, int time)
{
	phil->state = state;
	// log(phil, THINKING);
}

void philo_eat(t_philo *phil)
{
	int time;

	time = get_time();
	if (phil->next_wake_time >= time)
	{
		philo_set_state(phil, SLEEPING, phil->next_wake_time);
	}
}

void philo_think(t_philo *phil)
{
	t_appstate	*state;
	int			time;

	state = get_appstate();
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->fork_left);
		pthread_mutex_lock(phil->fork_right);
	}
	else
	{
		pthread_mutex_lock(phil->fork_right);
		pthread_mutex_lock(phil->fork_left);
	}
	time = get_time();
	philo_set_state(phil, EATING, time);
	phil->next_sleep_time = time + state->tte;
	phil->next_wake_time = phil->next_sleep_time + state->tts;
	phil->next_death_time = time + state->ttd;
}

void philo_sleep(t_philo *phil)
{
	int time;

	time = get_time();
	if (phil->next_wake_time >= time)
	{
		philo_set_state(phil, THINKING, phil->next_wake_time);
	}
}

void *philo_run(void *data)
{
	t_philo *phil;

	phil = (t_philo *)data;
	while (is_running())
	{
		if (EATING == phil->state)
			philo_eat(phil);
		else if (SLEEPING == phil->state)
			philo_sleep(phil);
			//check if sleeptime finished
		else if (THINKING == phil->state)
			philo_think(phil);
	}
}

void *giatros_run(t_appstate *state)
{
	int ctr;
	int time;

	ctr = 0;
	while(is_running())
	{
		time = get_time();
		if (state->philos[ctr].next_death_time < time)
			*get_running() = 0;
		ctr == ++ctr % state->nbr_philos;
	}
}

void pratiritis_run()
{
	
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