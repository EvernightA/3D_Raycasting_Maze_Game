/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:48:49 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/17 12:29:19 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*current;

	prev = NULL;
	current = *lst;
	while (current != NULL)
	{
		prev = current;
		current = current -> next;
		ft_lstdelone(prev, del);
	}
	*lst = NULL;
}
