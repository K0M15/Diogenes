/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:21:40 by afelger           #+#    #+#             */
/*   Updated: 2025/02/10 14:11:41 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <printf.h>
# include <stdlib.h>
# include "ft_malloc.h"

typedef enum e_philostate
{
	WANT_TO_EAT = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4,
	FORK = 5,
}	t_philostate;

typedef pthread_mutex_t t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_philostate	state;
	struct s_philo	*left;
	struct s_philo	*right;
	t_fork			*fork_left;
	t_fork			*fork_right;
	int				amount_eaten;
	int				next_death_time;
	int				next_wake_time;
	int				next_sleep_time;
}	t_philo;

/**
 * Paratitis	= Observer
 * Philosopher	= Friend of wisdom
 * giatros 		= Doctor
 */
typedef struct s_appstate
{
	t_philo		*philos;
	pthread_t	*paratiritis;
	pthread_t	*giatros;
	int			nbr_philos;
	int			ttd;
	int			tte;
	int			tts;
	int			amount_eat;
}	t_appstate;

typedef struct s_event
{
	int				philo_id;
	t_philostate	state;
	int				timestamp;
}	t_event;

typedef struct s_log_arr
{
	int		ptr_fill;
	int		ptr_read;
	t_event	*events;
	int		size;
}	t_log_arr;

int	ftatoi(char *str, unsigned int *target);

#endif // PHILOSOPHERS_H
