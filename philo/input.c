/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:15:39 by afelger           #+#    #+#             */
/*   Updated: 2025/06/19 16:36:39 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int64_t	parse_string(char *str)
{
	int64_t	result;

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
	return (result);
}

static int	validate_state(t_appstate *state)
{
	if ((state->number_philos | state->time_to_die | state->time_to_eat
			| state->time_to_sleep | state->notepme) > INT32_MAX)
		return (1);
	if (state->number_philos > UINT32_MAX)
		return (1);
	return (0);
}

int	parse_input(int argc, char **argv, t_appstate *state)
{
	state->notepme = 0;
	if (argc > 6 || argc < 5)
		return (1);
	state->number_philos = parse_string(argv[1]);
	state->time_to_die = parse_string(argv[2]);
	state->time_to_eat = parse_string(argv[3]);
	state->time_to_sleep = parse_string(argv[4]);
	if (argc == 6)
		state->notepme = parse_string(argv[5]);
	if (validate_state(state))
		return (1);
	return (0);
}
