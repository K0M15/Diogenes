/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:26:00 by afelger           #+#    #+#             */
/*   Updated: 2025/06/19 15:46:53 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(enum e_messagetxt msg, t_speaker *speaker)
{
	static t_speaker	*err_speaker;

	if (speaker != NULL)
		err_speaker = speaker;
	if (msg != NO_MESSAGE)
		add_message(RED, msg, UINT32_MAX, err_speaker);
}

void	display_usage(void)
{
	printf("usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
}

int	add_message(enum e_textcolor color, enum e_messagetxt msg,
	uint32_t phil_id, t_speaker *speaker)
{
	t_message	*new_msg;

	new_msg = malloc(sizeof(t_message));
	if (!new_msg)
		return (ft_error(MEM_ERR, NULL), 1);
	new_msg->color = color;
	new_msg->msg = msg;
	new_msg->time = ft_gettime();
	new_msg->phil_id = phil_id;
	new_msg->next = NULL;
	pthread_mutex_lock(&(speaker->lock_write));
	speaker->write->next = new_msg;
	speaker->write = new_msg;
	pthread_mutex_unlock(&(speaker->lock_write));
	return (0);
}

char	*get_message(enum e_messagetxt msg)
{
	if (msg == RETRIEVE_TIME_ERR)
		return (MSG_RETRIEVE_TIME_ERR);
	else if (msg == THREAD_INIT_ERR)
		return (MSG_THREAD_INIT_ERR);
	else if (msg == THREAD_JOIN_ERR)
		return (MSG_THREAD_JOIN_ERR);
	if (msg == MUTEX_INIT_ERR)
		return (MSG_MUTEX_INIT_ERR);
	if (msg == MUTEX_LOCK_ERR)
		return (MSG_MUTEX_LOCK_ERR);
	if (msg == PHIL_FORK)
		return (MSG_PHIL_FORK);
	if (msg == PHIL_SLEEP)
		return (MSG_PHIL_SLEEP);
	if (msg == PHIL_EAT)
		return (MSG_PHIL_EAT);
	if (msg == PHIL_THINK)
		return (MSG_PHIL_THINK);
	if (msg == PHIL_DIE)
		return (MSG_PHIL_DIE);
	return (MSG_DEFAULT_ERROR);
}

int	free_messages(t_message *msg)
{
	t_message	*next;

	while (msg)
	{
		if (msg->phil_id == UINT32_MAX)
		{
			printf("\033[%d;m%llu %d %s\033[0m",
				msg->color,
				msg->time,
				msg->phil_id,
				get_message(msg->msg));
		}
		next = msg->next;
		free(msg);
		msg = next;
	}
	return (0);
}
