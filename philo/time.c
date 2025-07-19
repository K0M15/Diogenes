/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:25:31 by afelger           #+#    #+#             */
/*   Updated: 2025/07/17 12:31:36 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t ft_gettime(void)
{
    static uint64_t start;
    struct timeval current;

    if (gettimeofday(&current, NULL))
        return (ft_error(RETRIEVE_TIME_ERR, NULL), 0);
    
    if (start == 0)
    {
        start = current.tv_sec * 1000 + (current.tv_usec / 1000);
        return 0;
    }
    
    return (current.tv_sec * 1000 + (current.tv_usec / 1000)) - start;
}

void	ft_sleep(int ms, t_appstate *state)
{
	uint64_t	start;
	uint64_t	curr;

	start = ft_gettime();
	curr = start;
	while (start + ms > curr && check_running(state))
	{
		curr = ft_gettime();
		usleep((((start + ms * 10) - curr) / 20));
	}
}
