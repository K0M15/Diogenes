/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:35:24 by afelger           #+#    #+#             */
/*   Updated: 2025/04/29 16:14:17 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <errno.h>

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
	time = ft_get_ms();
	while (i < amount)
	{
		if (init_philo(&((*phil)[i]), i, time, state))
			return (ft_putstr_fd(ERR_COLOR"Error setting up a philo\n"RES_COLOR,
				2), remove_philo(i, *phil), 1);	//Remove all created...
		i+= 2;
	}
	i = 1;
	while (i < amount)
	{
		if (init_philo(&((*phil)[i]), i, time, state))
		{
			ft_putstr_fd(ERR_COLOR"Error setting up a philo\n"RES_COLOR, 2);
			return (remove_philo(i, *phil), 1);	//Remove all created...
		}
		i+= 2;
	}
	return (0);
}

int remove_philo(uint32_t amount, t_philosopher *phil)
{
	uint32_t i;
	uint32_t ret_code;
	uint32_t buffer;

	i = 0;
	ret_code = 0;
	while (i < amount)
	{
		// No such process
		buffer = pthread_detach(phil[i].thread);
		if (buffer)
		{
			ft_putstr_fd(ERR_COLOR"Error while deataching phil: ", 2); // DEBUG
			ft_putstr_fd(ft_itoa(i), 2); // DEBUG
			ft_putstr_fd(" Errcode: ", 2); // DEBUG
			ft_putstr_fd(ft_itoa(buffer), 2); // DEBUG
			ft_putstr_fd("\n", 2); // DEBUG
			ret_code &= buffer;
		}
		i++;
	}
	free(phil);
	return (ret_code);
}