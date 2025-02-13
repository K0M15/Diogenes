/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:56:44 by afelger           #+#    #+#             */
/*   Updated: 2025/02/06 14:00:30 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread.h"

typedef struct s_listelem
{
	void *data;
	pthread_mutex_t mut;
}	t_listelem;

typedef struct s_list
{
	head
}	t_list;

int list_init(t_list *arr)
{
}