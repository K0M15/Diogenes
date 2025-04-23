/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:07:58 by afelger           #+#    #+#             */
/*   Updated: 2025/04/23 15:28:48 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "libc.h"
# include "include/libft.h"

# define ERR_COLOR "\033[31;1m"
# define INFO_COLOR "\033[94;1m"
# define RES_COLOR "\033[0m"

typedef struct s_fork
{
	pthread_mutex_t mut_is_taken;
	pthread_mutex_t mut_taken;
	boolean_t		is_taken;
}	t_fork;

typedef struct s_philosopher
{
	uint32_t	id;
	pthread_t	thread;
	uint32_t	amount_eaten;
	uint64_t	ate_last;
	void		*state;
	t_fork		*forks[2];
}	t_philosopher;

typedef struct s_appstate
{
	uint32_t		number_of_philosophers;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	int64_t			each_must_eat;
	pthread_mutex_t	mut_is_stopped;
	boolean_t		is_stopped;
	t_fork			*forks;
	t_philosopher	*philos;
	pthread_t		observer;
}	t_appstate;

enum args_err
{
	NULL_PHILOS = 0,
	NULL_TIME2DIE,
	NULL_TIME2EAT,
	NULL_TIME2SLEEP,
	NULL_EACH_MUST_EAT,
	WRONG_AMOUNT_OF_ARGS,
};

t_appstate	*parse_args(int argc, char **argv);
void		*parse_error(enum args_err err);
void		display_info();

void		run();
void		wait_for_end();

// FORKS
int			init_fork(t_fork *fork);
int 		create_tableware(uint32_t amount, t_fork **forks);
boolean_t	free_tableware(uint32_t amount, t_fork *forks);
boolean_t	get_fork(t_fork *fork, t_philosopher *phil);
void		drop_forks(t_philosopher *phil);

// PHILO - Object
int			init_philo(t_philosopher *phil, uint32_t id, uint64_t init_time, t_appstate *state);
int			create_school(uint32_t amount, t_philosopher **phil, t_appstate *state);
int			remove_philo(uint32_t amount, t_philosopher *phil);

// PHILO - Implemtation
void		*phil_main();

// OBSERVER
int			init_observer(pthread_t *observer, t_appstate *state);
void		*obs_main();

//TIME
uint64_t	ft_get_us();

#endif // PHILOSOPHERS_H
