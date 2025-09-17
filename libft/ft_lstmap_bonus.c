/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:05:15 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/19 11:34:47 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*prev;
	t_list	*tmp;
	t_list	*new_head;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	new = ft_lstnew(f(tmp -> content));
	tmp = tmp -> next;
	prev = new;
	new_head = new;
	while (tmp != NULL)
	{
		new = ft_lstnew(f(tmp -> content));
		if (new == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		prev -> next = new;
		prev = new;
		tmp = tmp -> next;
	}
	return (new_head);
}
