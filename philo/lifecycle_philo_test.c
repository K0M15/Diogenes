
#include "philosophers.h"
#include <pthread.h>

int main()
{
	// t_philosopher phil;
	t_appstate state;

	state.time_to_die = 800;
	state.time_to_eat = 200;
	state.time_to_sleep = 200;
	state.each_must_eat = 1;
	state.number_of_philosophers = 200;
	state.is_stopped = 0;
	if (pthread_mutex_init(&state.mut_is_stopped, NULL)
		|| pthread_mutex_init(&state.mut_write, NULL))
	{
		ft_putstr_fd(ERR_COLOR"Error setting up the stopped mutex\n"RES_COLOR, 2);
		return (1);
	}
	if (create_tableware(state.number_of_philosophers, &state.forks))
	{
		ft_putstr_fd(ERR_COLOR"Error setting up the tableware\n"RES_COLOR, 2);
		return (1);
	}
	if (init_observer(&state.observer, &state))
	{
		ft_putstr_fd(ERR_COLOR"Error setting up the observer\n"RES_COLOR, 2);
		return (1);
	}
	if (create_school(state.number_of_philosophers, &state.philos, &state))
	{
		ft_putstr_fd(ERR_COLOR"Error setting up the school\n"RES_COLOR, 2);
		return (1);
	}
	// pthread_join((state.philos[0].thread), NULL);
	pthread_join((state.observer), NULL);
	remove_philo(state.number_of_philosophers, state.philos); // First is already exited
	pthread_mutex_lock(&state.mut_write);
	ft_printf(INFO_COLOR"%d Exited successfull \n"RES_COLOR, ft_get_ms());
	pthread_mutex_unlock(&state.mut_write);
	return (0);
}
