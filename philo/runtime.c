/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:26:39 by afelger           #+#    #+#             */
/*   Updated: 2025/04/23 15:31:09 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void wait_for_end(t_appstate *state)
{
	if (pthread_join(state->observer, NULL))
		ft_putstr_fd(ERR_COLOR "Error on Observer join\n" RES_COLOR, 2);
}

void run(t_appstate *state)
{
	wait_for_end(state);
	printf(INFO_COLOR "Ended\n" RES_COLOR);
	if (free_tableware(state->number_of_philosophers, state->forks)
		|| remove_philo(state->number_of_philosophers, state->philos))
		ft_putstr_fd(ERR_COLOR "Error while deleting objects\n" RES_COLOR, 2);
}