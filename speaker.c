/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speaker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:18 by afelger           #+#    #+#             */
/*   Updated: 2025/05/20 14:43:52 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

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
}

int	speaker_main(t_appstate *app)
{
	t_speaker	*speaker;
	uint64_t lastWritePos;
	t_message	*msg;

	speaker = &app->speaker;
	while (check_running(app))
	{
		lastWritePos = ft_mutex_getvalue(&(speaker->write_pos));
		while (lastWritePos >= speaker->read_pos)
		{
			msg = &(speaker->messages[speaker->read_pos]);
			if (msg->phil_id == UINT32_MAX)
				printf("%d %s", msg->time, get_message(msg->msg));
			else
				printf("%d %d %s", msg->time, msg->phil_id, get_message(msg->msg));
			speaker->read_pos++;
		}
		usleep(100);
	}
}

int	init_speaker(t_speaker *speaker, t_appstate *app)
{
	memset(&(speaker->messages), 0, MESSAGE_BUFFER_SIZE * sizeof(t_message));
	create_ft_mutex(&(speaker->read_pos));
	create_ft_mutex(&(speaker->write_pos));
	pthread_create(&(speaker->thread), NULL, speaker_main, app);
}
