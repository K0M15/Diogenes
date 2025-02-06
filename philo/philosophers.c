/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:19:42 by afelger           #+#    #+#             */
/*   Updated: 2025/02/06 16:05:31 by afelger          ###   ########.fr       */
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
	static int running;

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
	if (0 == starttime)
		starttime = t.tv_usec;
	return (t.tv_usec - starttime);
}

t_appstate *get_appstate(void)
{
	static t_appstate appstate;
	
	return (&appstate);
}

t_log_arr *log_init()
{
	int			philo_amt;
	t_log_arr	*arr;

	philo_amt = get_appstate()->nbr_philos;
	arr = malloc(sizeof(t_log_arr));
	arr->ptr_fill = 0;
	arr->ptr_read = 0;
	arr->events = malloc(sizeof(t_event) * philo_amt * 2);
	arr->size = philo_amt * 2;
	return (arr);
}

t_log_arr *get_log()
{
	static t_log_arr *arr;

	if (arr == NULL)
		arr = log_init();
	return (arr);
}

void add_log(int timestamp, int philo_id, t_philostate state)
{
	static t_log_arr	*arr;

	if (NULL == arr)
		arr = get_log();
	arr->events[arr->ptr_fill].philo_id = philo_id;
	arr->events[arr->ptr_fill].state = state;
	arr->events[arr->ptr_fill].timestamp = timestamp;
	arr->ptr_fill += 1;
	if (arr->size <= arr->ptr_fill)
		arr->ptr_fill = 0;
	if (arr->ptr_fill == arr->ptr_read)
		assert(0);	//Wrap around: logs have overtaken display
}

t_event *get_next_log()
{
	static t_log_arr	*arr;
	t_event				*result;

	if (NULL == arr)
		arr = get_log();
	if (arr->ptr_read == arr->ptr_fill)
		return (NULL);
	result = &arr->events[arr->ptr_read];
	arr->ptr_read += 1;
	if (arr->size <= arr->ptr_read)
		arr->ptr_read = 0;
	return (result);
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
	add_log(time, phil->id, phil->state);
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

	time = get_time();
	state = get_appstate();
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->fork_left);
		add_log(time, phil->id, FORK);
		pthread_mutex_lock(phil->fork_right);
	}
	else
	{
		pthread_mutex_lock(phil->fork_right);
		add_log(time, phil->id, FORK);
		pthread_mutex_lock(phil->fork_left);
	}
	time = get_time();
	add_log(time, phil->id, FORK);
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
		philo_set_state(phil, THINKING, phil->next_wake_time);
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
	return (NULL);
}

void *giatros_run(void *args)
{
	int ctr;
	int time;
	t_appstate *state;

	state = (t_appstate *)args;
	ctr = 0;
	while(is_running())
	{
		time = get_time();
		if (state->philos[ctr].next_death_time < time)
		{
			*get_running() = 0;
			add_log(time, state->philos[ctr].id, DIED);
		}
		ctr++;
		ctr %= state->nbr_philos;
	}
	return (NULL);
}

void *pratiritis_run(void *args)
{
	t_event	*display;
	t_appstate *state;

	state = (t_appstate *)args;
	display = get_next_log();
	while (get_running())
	{
		if (NULL == display)
			break ;
		if (display->state == THINKING)
			printf("%d %d is thinking", display->timestamp, display->philo_id);
		else if (display->state == EATING)
			printf("%d %d is eating", display->timestamp, display->philo_id);
		else if (display->state == SLEEPING)
			printf("%d %d is sleeping", display->timestamp, display->philo_id);
		else if (display->state == FORK)
			printf("%d %d is has taken a fork", display->timestamp, display->philo_id);
		else if (display->state == DIED)
		{
			printf("%d %d died", display->timestamp, display->philo_id);
			return (NULL);
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo	*phils;
	t_appstate *state;
	int ctr = -1;

	(void) argc;
	(void) argv;
	state = get_appstate();
	state->nbr_philos = 1;
	state->ttd = 600;
	state->tte = 100;
	state->tts = 100;
	state->amount_eat = -1;
	phils = malloc(sizeof(t_philo) * state->nbr_philos);
	if (phils == NULL)
		exit(0);
	*get_running() = 1;
	pthread_create(state->giatros, NULL, giatros_run, state);
	pthread_create(state->paratiritis, NULL, pratiritis_run, state);
	while (++ctr < state->nbr_philos)
		pthread_create(&phils[0].thread, NULL, philo_run, &phils[0]);
	pthread_join(*state->giatros, NULL);
}