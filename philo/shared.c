/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:12:59 by afelger           #+#    #+#             */
/*   Updated: 2025/04/25 17:27:56 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

boolean_t check_running(t_appstate *state)
{
	boolean_t result;
	
	pthread_mutex_lock(&state->mut_is_stopped);
	result = state->is_stopped;
	pthread_mutex_unlock(&state->mut_is_stopped);
	return (result);
}