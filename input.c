/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:15:39 by afelger           #+#    #+#             */
/*   Updated: 2025/06/03 11:40:59 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int64_t  parseString(char *str)
{
	int64_t result;

	result = 0;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		result = result * 10 + *str - '0';
		str++;
	}
	return result;
}

static int validateState(t_appstate *state)
{
	if ((state->number_philos & state->time_to_die & state->time_to_eat
		& state->time_to_sleep & state->notepme) > INT32_MAX)	// This could lead to errors since all vals are UINT32_T and compare to int32. but first bit will display error
		return (1);
	if (state->number_philos > UINT32_MAX)
		return (1);
	return (0);
}

int parse_input(int argc, char **argv, t_appstate *state)
{
	state->notepme = 0;
	if (argc > 6 || argc < 5)
		return (1);
	state->number_philos = parseString(argv[1]);
	state->time_to_die = parseString(argv[2]);
	state->time_to_eat = parseString(argv[3]);
	state->time_to_sleep = parseString(argv[4]);
	if (argc == 6)
		state->notepme = parseString(argv[5]);
	if (validateState(state))
		return (1);
	return(0);
}