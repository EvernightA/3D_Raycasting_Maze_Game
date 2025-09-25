/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 11:06:54 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_line	*bresenham_line(t_point *begin, t_point *end)
{
	int delta_x;
	int delta_y;
	int i;
	t_point next_point;
	t_line *head;
	t_line *new_node;
	
	i = 0;
	head = NULL;
	delta_x = end->x - begin->x;
	delta_y = end->y - begin->y;
	begin->dp = 2 * delta_y - delta_x;
	while (1)
	{
		if ((begin->x == end->x && begin->y == end->y) || i > delta_x - 1)
		{
			new_node = ft_linenew(*begin);
			ft_lineadd_back(&head,new_node);
			break ;
		}
		new_node = ft_linenew(*begin);
		ft_lineadd_back(&head,new_node);
		if (i == 0)
		{
			head = new_node;
		}
		if (begin->dp < 0)
		{
			next_point.dp = begin->dp + 2 * delta_y;
			next_point.x = begin->x + 1;
			next_point.y = begin->y;
		}
		else
		{
			next_point.dp = begin->dp + 2 * (delta_y - delta_x);
			next_point.x = begin->x + 1;
			next_point.y = begin->y + 1; 
		}
		begin = &next_point;
		i++;
	}
	return (head);
}
