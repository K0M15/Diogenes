/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:56:52 by afelger           #+#    #+#             */
/*   Updated: 2024/10/21 08:54:28 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*lst_new_del(void *cnt, void *(*f)(void *))
{
	t_list	*new;

	new = ft_lstnew(NULL);
	if (new == NULL)
		return (NULL);
	new->content = f(cnt);
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	result = lst_new_del(lst->content, f);
	if (result == NULL)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		current = lst_new_del(lst->content, f);
		ft_lstadd_back(&result, current);
		lst = lst->next;
		if (current == NULL)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
	}
	return (result);
}

// void *t_len(void *mem)
// {
// 	long *x = malloc(sizeof(long *));
// 	*x = ft_strlen(mem);
// 	return ((void *)x);
// }

// void rem(void *mem)
// {
// 	free(mem);
// }

// int main()
// {
// 	t_list *list1 = ft_lstnew("Some");
// 	t_list *list2 = ft_lstnew("Som");
// 	t_list *list3 = ft_lstnew("So");
// 	t_list *list4 = ft_lstnew("S");

// 	list1->next = list2;
// 	list2->next = list3;
// 	list3->next = list4;

// 	t_list *res = ft_lstmap(list1, t_len, rem);
// 	res--;
// }