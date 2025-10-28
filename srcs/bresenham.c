/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/28 08:34:29 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_line	*bresenham_line(t_point *begin, t_point *end)
{
	int delta_x;
	int delta_y;
	int i;
	int x_step;
	int y_step;
	t_point next_point;
	t_line *head;
	t_line *new_node;
	
	i = 0;
	head = NULL;
	delta_x = abs(end->x - begin->x);
	delta_y = abs(end->y - begin->y);
	if (begin->x < end->x)
		x_step = 1;
	else	
		x_step = -1;
	if (begin->y < end->y)
		y_step = 1;
	else
		y_step = -1;
	if (abs(delta_y) < abs(delta_x))
		begin->dp = 2 * (delta_y - delta_x);
	else
		begin->dp = 2 * (delta_x - delta_y);
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
			if (abs(delta_y) < abs(delta_x))
				next_point.dp = begin->dp + 2 * delta_y;
			else
				next_point.dp = begin->dp + 2 * delta_x;
		}
		else
		{
			if (abs(delta_y) < abs(delta_x))
				next_point.dp = begin->dp + 2 * (delta_y - delta_x);
			else
				next_point.dp = begin->dp + 2 * (delta_x - delta_y);
		}
		next_point.x = begin->x + x_step;
		next_point.y = begin->y + y_step;
		begin = &next_point;
		i++;
	}
	return (head);
}
