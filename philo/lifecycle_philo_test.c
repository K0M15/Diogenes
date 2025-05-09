
#include "philosophers.h"
#include <pthread.h>

int main()
{
	// t_philosopher phil;
	t_appstate state;

	state.time_to_die = 500;
	state.time_to_eat = 5000;
	state.time_to_sleep = 100;
	state.each_must_eat = 10;
	state.number_of_philosophers = 4;
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
	if (init_observer(&state.observer, &state) || create_school(state.number_of_philosophers, &state.philos, &state))
	// if (create_school(state.number_of_philosophers, &state.philos, &state))
	{
		ft_putstr_fd(ERR_COLOR"Error setting up the school\n"RES_COLOR, 2);
		return (1);
	}
	pthread_join((state.philos[0].thread), NULL);
	// pthread_join((state.observer), NULL);
	remove_philo(state.number_of_philosophers, state.philos); // First is already exited
	ft_printf(INFO_COLOR"Exit successfull\n"RES_COLOR);
	return (0);
}