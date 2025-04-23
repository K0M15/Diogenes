/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:08:33 by afelger           #+#    #+#             */
/*   Updated: 2025/04/23 15:17:12 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_info(void)
{
	ft_putstr_fd("usage: philosophers  number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n", 1);
}

void	*parse_error(enum args_err err)
{
	if (err == NULL_PHILOS)
		ft_putstr_fd(ERR_COLOR "philosophers: wrong amount of philos\
defined\n" RES_COLOR, 2);
	else if (err == NULL_TIME2DIE)
		ft_putstr_fd(ERR_COLOR "philosophers: wrong amount of time_to_die\
defined\n" RES_COLOR, 2);
	else if (err == NULL_TIME2EAT)
		ft_putstr_fd(ERR_COLOR "philosophers: wrong amount of time_to_eat\
defined\n" RES_COLOR, 2);
	else if (err == NULL_TIME2SLEEP)
		ft_putstr_fd(ERR_COLOR "philosophers: wrong amount of time_to_sleep\
defined\n" RES_COLOR, 2);
	else if (err == NULL_EACH_MUST_EAT)
		ft_putstr_fd(ERR_COLOR "philosophers: wrong amount of number_of_times\
_each_philosopher_must_eat defined\n" RES_COLOR, 2);
	else if (err == WRONG_AMOUNT_OF_ARGS)
		ft_putstr_fd(ERR_COLOR"philosophers: wrong amount of args entered\n"
			RES_COLOR, 2);
	display_info();
	return (NULL);
}

static int check_appstate(t_appstate *state)
{
	if (state->each_must_eat == 0)
		return (parse_error(NULL_EACH_MUST_EAT) != NULL);
	else if (state->number_of_philosophers == 0)
		return (parse_error(NULL_PHILOS) != NULL);
	else if (state->time_to_die == 0)
		return (parse_error(NULL_TIME2DIE) != NULL);
	else if (state->time_to_eat == 0)
		return (parse_error(NULL_TIME2EAT) != NULL);
	else if (state->time_to_sleep == 0)
		return (parse_error(NULL_TIME2SLEEP) != NULL);
	return (0);
}

t_appstate	*parse_args(int argc, char **argv)
{
	t_appstate	*state;

	state = malloc(sizeof(t_appstate));
	if (state == NULL || argc < 5 || argc > 6)
		return ((t_appstate *)parse_error(WRONG_AMOUNT_OF_ARGS));
	state->number_of_philosophers = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->each_must_eat = -1;
	if (argc == 6)
		state->each_must_eat = ft_atoi(argv[5]);
	if (check_appstate(state))
		return (free(state), NULL);
	return (state);
}
