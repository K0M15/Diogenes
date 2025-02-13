/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:19:42 by afelger           #+#    #+#             */
/*   Updated: 2025/02/10 14:59:01 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <assert.h>

#include "string.h"
#include "stdlib.h"
int ftlog(const char *str)
{
	write(1, str, strlen(str));
	return 0;
}

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
	if (last != NULL)
	{
		philo->left = last;
		philo->left->right = philo;
	}
	philo->amount_eaten = 0;
	philo->next_sleep_time = 0;		// FINISH EATING
	philo->next_wake_time = 0;
}

int philos_init(void)
{
	t_appstate *state;
	int c;

	c = 0;
	state = get_appstate();
	state->philos = malloc(sizeof(t_philo) * state->nbr_philos);
	if (state->philos == NULL)
		return (0);
	while (c < state->nbr_philos){
		if (c == 0)
			philo_init(&state->philos[c], c, NULL);
		else
			philo_init(&state->philos[c], c, &state->philos[c-1]);
		c++;
	}
	state->philos[0].left = &state->philos[c - 1];
	return (1);
}

int philos_create_forks(void)
{
	t_appstate *state;
	pthread_mutex_t	*forks;
	int c;

	c = 0;
	state = get_appstate();
	forks = malloc(state->nbr_philos * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (0);
	while (c < state->nbr_philos)
	{
		pthread_mutex_init(&forks[c], NULL);
		state->philos[c].fork_left = &forks[c];
		if (c + 1 < state->nbr_philos)
			state->philos[c].fork_right = &forks[c + 1];
		else
			state->philos[c].fork_right = &forks[0];
		c++;
	}
	return (1);
}

void	philo_set_state(t_philo *phil, t_philostate state, int time)
{
	phil->state = state;
	add_log(time, phil->id, phil->state);
}

void	philo_eat(t_philo *phil)
{
	int time;

	time = get_time();
	if (phil->next_wake_time >= time)
	{
		philo_set_state(phil, SLEEPING, phil->next_wake_time);
	}
}

void	philo_think(t_philo *phil)
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

void	philo_sleep(t_philo *phil)
{
	int time;

	time = get_time();
	if (phil->next_wake_time >= time)
		philo_set_state(phil, THINKING, phil->next_wake_time);
}

void	wait_running(void)
{
	while (!is_running())
	{
		usleep(1);
	}
	ftlog("Start run\n");
}

void	*philo_run(void *data)
{
	t_philo *phil;

	phil = (t_philo *)data;
	wait_running();
	philo_set_state(phil, THINKING, 0);
	while (is_running())
	{
		ftlog("Philo loop\n");
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

void	*giatros_run(void *args)
{
	int ctr;
	int time;
	t_appstate *state;

	state = (t_appstate *)args;
	ctr = 0;
	wait_running();
	while(is_running())
	{
		ftlog("doctor loop\n");
		time = get_time();
		if (state->philos[ctr].next_death_time < time)
		{
			*get_running() = 0;
			add_log(time, state->philos[ctr].id, DIED);
		}
		ctr++;
		ctr %= state->nbr_philos;
	}
	ftlog("doctor out\n");
	return (NULL);
}

void	*paratiritis_run(void *args)
{
	t_event	*display;
	t_appstate *state;

	state = (t_appstate *)args;
	display = get_next_log();
	wait_running();
	while (is_running())
	{
		ftlog("Paratiritis loop\n");
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
	ftlog("Paratiritis out\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	// t_philo	*phils;
	t_appstate *katástasi;
	int ctr = -1;

	(void) argc;
	(void) argv;
	katástasi = get_appstate();
	katástasi->nbr_philos = 1;
	katástasi->ttd = 600;
	katástasi->tte = 100;
	katástasi->tts = 100;
	katástasi->amount_eat = -1;
	philos_init();
	philos_create_forks();
	katástasi->giatros = malloc(sizeof(pthread_t));
	katástasi->paratiritis = malloc(sizeof(pthread_t));
	if (katástasi->philos == NULL || katástasi->giatros == NULL || katástasi->paratiritis == NULL)
		ftlog("Mem init failed\n");
		// exit(0);
	pthread_create(katástasi->giatros, NULL, giatros_run, katástasi);
	pthread_create(katástasi->paratiritis, NULL, paratiritis_run, katástasi);
	while (++ctr < katástasi->nbr_philos)
		pthread_create(&katástasi->philos[ctr].thread, NULL, philo_run, &katástasi->philos[ctr]) && ftlog("init philo\n");
	*get_running() = 1;
	pthread_join(*katástasi->giatros, NULL);
	// cleanup()
}