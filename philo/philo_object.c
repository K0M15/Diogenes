/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:35:24 by afelger           #+#    #+#             */
/*   Updated: 2025/04/22 18:50:07 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	init_philo(t_philosopher *phil, uint32_t id, uint64_t init_time)
{
	memset(phil, 0, sizeof(t_philosopher));
	phil->ate_last = init_time;
	phil->id = id;
	pthread_create(&phil->thread, NULL, phil_main, phil);
}

int	create_school(uint32_t amount, t_philosopher **phil)
{
	uint32_t i;
	uint64_t time;

	i = 0;
	*phil = malloc(sizeof(t_philosopher) * amount);
	time = ft_get_us();
	while (i < amount)
	{
		if (init_philo(&(*phil[i]), i, time))
			return (1);	//Remove all created...
		i++;
	}
	return (0);
}

int remove_philo(uint32_t amount, t_philosopher *phil)
{
	int i;

	i = 0;
	while (i < amount)
	{
		pthread_detach(&phil[i].thread);
		i++;
	}
	free(phil);
}