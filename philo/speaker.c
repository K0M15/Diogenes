/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speaker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:18 by afelger           #+#    #+#             */
/*   Updated: 2025/06/17 17:10:00 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

int	add_message(enum e_textcolor color, enum e_messagetxt msg,
	uint32_t phil_id, t_speaker *speaker)
{
	t_message	*new_msg;

	new_msg = malloc(sizeof(t_message));
	if (!new_msg)
		return (ft_error(MEM_ERR), 1);
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
		next = msg->next;
		free(msg);
		msg = next;
	}
	return (0);
}

int	speaker_main(t_appstate *state)
{
	t_speaker	*speaker;
	t_message	*next;

	speaker = &(state->speaker);
	while (check_running(state))
	{
		pthread_mutex_lock(&(speaker->lock_write));
		if (speaker->read == speaker->write)
		{
			pthread_mutex_unlock(&(speaker->lock_write));
			continue ;
		}
		pthread_mutex_unlock(&(speaker->lock_write));
		printf("\033[%d;m%llu %d %s\033[0m",
			speaker->read->next->color,
			speaker->read->next->time,
			speaker->read->next->phil_id,
			get_message(speaker->read->next->msg));
		next = speaker->read->next;
		free(speaker->read);
		speaker->read = next;
	}
	return (0);
}

void	*speaker_wapper(void *args)
{
	speaker_main((t_appstate *)args);
	free_messages(((t_appstate *)args)->speaker.read);
	return (NULL);
}

int	init_speaker(t_speaker *speaker, t_appstate *app)
{
	(void) app;
	speaker->read = malloc(sizeof(t_message));
	if (!speaker->read || pthread_mutex_init(&speaker->lock_write, NULL))
		return (ft_error(MEM_ERR), 1);
	speaker->write = speaker->read;
	speaker->read->next = NULL;
	speaker->read->color = RED;
	if (pthread_create(&(speaker->thread), NULL, speaker_wapper, (void *)app))
		return (ft_error(THREAD_INIT_ERR), 1);
	return (0);
}
