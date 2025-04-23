/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:35:24 by afelger           #+#    #+#             */
/*   Updated: 2025/04/23 15:28:28 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	init_philo(t_philosopher *phil, uint32_t id, uint64_t init_time,
	t_appstate *state)
{
	memset(phil, 0, sizeof(t_philosopher));
	phil->ate_last = init_time;
	phil->id = id;
	phil->state = state;
	if (pthread_create(&phil->thread, NULL, phil_main, phil))
		return (1);
	return (0);
}

int	create_school(uint32_t amount, t_philosopher **phil, t_appstate *state)
{
	uint32_t i;
	uint64_t time;

	i = 0;
	*phil = malloc(sizeof(t_philosopher) * amount);
	time = ft_get_us();
	while (i < amount)
	{
		if (init_philo(&((*phil)[i]), i, time, state))
			return (remove_philo(i, *phil), 1);	//Remove all created...
		i++;
	}
	return (0);
}

int remove_philo(uint32_t amount, t_philosopher *phil)
{
	uint32_t i;

	i = 0;
	while (i < amount)
	{
		pthread_detach(phil[i].thread);
		i++;
	}
	free(phil);
	return (0);
}