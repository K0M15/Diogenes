/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:21:40 by afelger           #+#    #+#             */
/*   Updated: 2025/02/03 19:07:14 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "pthread.h"
# include "sys/time.h"

typedef enum e_philostate
{
	WANT_TO_EAT = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4,
}	t_philostate;

typedef pthread_mutex_t t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_philostate	state;
	struct s_philo	*left;
	struct s_philo	*right;
	t_fork			*left;
	t_fork			*right;
	int				amount_eaten;
	int				next_death_time;
}	t_philo;

/**
 * Paratitis = Observer
 * Philosopher = Friend of wisdom
 */
typedef struct s_appstate
{
	t_philo *philos;
	pthread_t	*paratiritis;
	int		nbr_philos;
	int		ttd;
	int		tte;
	int		tts;
	int		amount_eat;
}	t_appstate;

typedef struct s_event
{
	int				philo_id;
	t_philostate	state;
}	t_event;

#endif // PHILOSOPHERS_H
