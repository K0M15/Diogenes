/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:38:45 by afelger           #+#    #+#             */
/*   Updated: 2025/02/01 12:26:09 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_philo(int id)
{
	t_philo *phil;

	phil = malloc(sizeof(t_philo));
	pthread_create(phil->thread, )
}