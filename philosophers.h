/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:14:51 by afelger           #+#    #+#             */
/*   Updated: 2025/06/05 15:09:59 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHER_H
# define PHILOSPHER_H

# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>

# define MSG_RETRIEVE_TIME_ERR "Error while retrieving time\n"
# define MSG_THREAD_INIT_ERR "Error while starting thread\n"
# define MSG_THREAD_JOIN_ERR "Error while joining thread\n"
# define MSG_MUTEX_INIT_ERR "Error while initializing a mutex\n"
# define MSG_MUTEX_LOCK_ERR "Error while locking a mutex\n"
# define MSG_MEM_ERR "Error while locking a mutex\n"
# define MSG_PHIL_FORK "has picked up a fork\n"
# define MSG_PHIL_SLEEP "is sleeping\n"
# define MSG_PHIL_EAT "is eating\n"
# define MSG_PHIL_THINK "is thinking\n"
# define MSG_PHIL_DIE "has died\n"
# define MSG_DEFAULT_ERROR "An error has occured\n"

# define MESSAGE_BUFFER_SIZE 1000

enum e_textcolor{
	RED = 31,
	GREEN = 32,
	BLUE = 94
};

enum e_messagetxt{
	DEFAULT_ERR,
	RETRIEVE_TIME_ERR,
	THREAD_INIT_ERR,
	THREAD_JOIN_ERR,
	MUTEX_INIT_ERR,
	MUTEX_LOCK_ERR,
	MEM_ERR,
	PHIL_FORK = 0x80,
	PHIL_SLEEP,
	PHIL_EAT,
	PHIL_THINK,
	PHIL_DIE
};

typedef struct s_message{
	enum e_textcolor	color;
	enum e_messagetxt	msg;
	uint64_t			time;
	uint32_t			phil_id;
	struct s_message	*next;
}	t_message;


typedef struct s_ft_mutex{
	pthread_mutex_t checklock;
	pthread_mutex_t locked;
	uint64_t		value;
}	t_ft_mutex;

typedef struct s_speaker {
	pthread_t	thread;
	pthread_mutex_t lock_write;
	t_message	*read;
	t_message	*write;
}	t_speaker;

typedef struct s_philosopher {
	uint8_t				id;
	t_speaker			*handle_speak;
	t_ft_mutex			has_eaten;
	pthread_t			thread;
	t_ft_mutex			last_ate;
	struct s_appstate	*state;
	t_ft_mutex			*forks[2];
}	t_philosopher;

typedef struct s_appstate {
	t_speaker		speaker;
	pthread_t		observer;
	t_ft_mutex		running;
	t_philosopher	*philosophers;
	t_ft_mutex		*forks;
	uint32_t		number_philos;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		notepme;
}	t_appstate;

uint64_t	ft_gettime();
void		ft_sleep(int ms, t_appstate *state);
void 		ft_error(enum e_messagetxt msg);
bool 		check_running(t_appstate *state);
bool 		stop_running(t_appstate *state);
void		drop_forks(t_philosopher *phil);

int		add_message(enum e_textcolor color, enum e_messagetxt msg, uint32_t phil_id, t_speaker *speaker);
bool		ft_mutex_lock(t_ft_mutex *mut);
void		ft_mutex_unlock(t_ft_mutex *mut);
bool		ft_mutex_setvalue(t_ft_mutex *mut, uint64_t value);
bool		ft_mutex_incvalue(t_ft_mutex *mut);
uint64_t	ft_mutex_getvalue(t_ft_mutex *mut);
uint32_t	create_ft_mutex(t_ft_mutex *mut);
uint32_t	destroy_ft_mutex(t_ft_mutex *mut);
int			parse_input(int argc, char **argv, t_appstate *state);


void	philo_main(t_philosopher *phil);
void	*philo_thread(void *arg);
void	*observer_wrapper(void *arg);
int		init_speaker(t_speaker *speaker, t_appstate *app);
#endif /* PHILOSPHER_H */