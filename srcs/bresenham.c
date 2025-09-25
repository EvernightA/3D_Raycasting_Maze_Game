/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 09:23:38 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_point	bresenham_line(t_point *begin, t_point *end)
{
	int delta_x;
	int delta_y;
	int i;
	t_point next_point;
	
	i = 0;
	delta_x = end->x - begin->x;
	delta_y = end->y - begin->y;
	begin->dp = 2 * delta_y - delta_x;
	while (1)
	{
		if ((begin->x == end->x && begin->y == end->y) || i > delta_x - 1)
			break ;
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
		printf("next = (%d, %d)\n", next_point.x, next_point.y);
		begin = &next_point;
		i++;
	}
	return (next_point);
}
