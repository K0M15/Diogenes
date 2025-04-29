/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:37:43 by afelger           #+#    #+#             */
/*   Updated: 2025/04/29 17:46:27 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	init_fork(t_fork *fork)
{
	if(pthread_mutex_init(&fork->mut_is_taken, NULL))
		return (1);
	if (pthread_mutex_init(&fork->mut_taken, NULL))
		return (1);
	fork->is_taken = FALSE;
	return (0);
}

int create_tableware(uint32_t amount, t_fork **forks)
{
	uint32_t i;

	i = 0;
	*forks = malloc(sizeof(t_fork) * amount);
	while (i < amount)
	{
		if (init_fork(&((*forks)[i])))
			return (free_tableware(i, *forks), 1);
		i++;
	}
	return (0);
}

boolean_t free_tableware(uint32_t amount, t_fork *forks)
{
	uint32_t i;
	boolean_t result;

	result = FALSE;
	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_destroy(&forks[i].mut_is_taken)
			|| pthread_mutex_destroy(&forks[i].mut_taken))
			result = TRUE;
		i++;
	}
	free(forks);
	return (result);
}

boolean_t get_fork(t_fork *fork, t_philosopher *phil)
{
	boolean_t	res;

	res = FALSE;
	pthread_mutex_lock(&fork->mut_is_taken);
	if (!fork->is_taken)
	{
		fork->is_taken = TRUE;
		res = TRUE;
		pthread_mutex_lock(&fork->mut_taken);
		phil->forks[phil->forks[1] == NULL] = fork;
	}
	pthread_mutex_unlock(&fork->mut_is_taken);
	return (res);
}

void	drop_forks(t_philosopher *phil)
{
	if (phil->forks[0] != NULL)
	{
		pthread_mutex_lock(&phil->forks[0]->mut_is_taken);
		phil->forks[0]->is_taken = FALSE;
		pthread_mutex_unlock(&phil->forks[0]->mut_is_taken);
		pthread_mutex_unlock(&phil->forks[0]->mut_taken);
		phil->forks[0] = NULL;
	}
	if (phil->forks[0] != NULL)
	{
		pthread_mutex_lock(&phil->forks[1]->mut_is_taken);
		phil->forks[1]->is_taken = FALSE;
		pthread_mutex_unlock(&phil->forks[1]->mut_is_taken);
		pthread_mutex_unlock(&phil->forks[1]->mut_taken);
		phil->forks[1] = NULL;
	}
}
