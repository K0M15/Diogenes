/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speaker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:18 by afelger           #+#    #+#             */
/*   Updated: 2025/06/23 17:52:47 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void find_and_speak_last(t_appstate *state)
{
	t_message *msg;

	msg = state->speaker.read;
	while (msg != NULL && msg->msg != PHIL_DIE)
		msg = msg->next;
	if (msg == NULL)
		// write(2, MSG_NO_DEATH_ERR, sizeof(MSG_NO_DEATH_ERR));
		return ;
	else
		printf("\033[%d;m%llu %d %s\033[0m",
			msg->color,
			msg->time,
			msg->phil_id,
			get_message(msg->msg));
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
	find_and_speak_last(state);
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
		return (ft_error(MEM_ERR, NULL), 1);
	speaker->write = speaker->read;
	speaker->read->next = NULL;
	speaker->read->color = RED;
	if (pthread_create(&(speaker->thread), NULL, speaker_wapper, (void *)app))
		return (ft_error(THREAD_INIT_ERR, NULL), 1);
	return (0);
}
