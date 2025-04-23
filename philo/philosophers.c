/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:50 by afelger           #+#    #+#             */
/*   Updated: 2025/04/23 15:30:24 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_app(t_appstate *state)
{
	if (init_observer(&state->observer, state))
		return (1);
	printf(INFO_COLOR "Created Observer\n" RES_COLOR);
	if (create_tableware(state->number_of_philosophers, &state->forks))
		return (1);
	printf(INFO_COLOR "Created Tableware\n" RES_COLOR);
	if (create_school(state->number_of_philosophers, &state->philos, state))
		return (1);
	printf(INFO_COLOR "Created School\n" RES_COLOR);
	return (0);
}

int main(int argc, char **argv)
{
	t_appstate *state;

	state = parse_args(argc, argv);
	if (state == NULL)
	{
		ft_putstr_fd(ERR_COLOR "Error on state parse\n" RES_COLOR, 2);
		return (1);
	}
	if (init_app(state))
	{
		ft_putstr_fd(ERR_COLOR "Error on app init\n" RES_COLOR, 2);
		return (1);
	}
	run(state);
}