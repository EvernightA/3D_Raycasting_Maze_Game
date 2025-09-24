/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/24 15:00:51 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	bresenham_line(t_point *begin, t_point *end)
{

	int delta_x;
	int delta_y;
	t_point next_point;
	
	delta_x = end->x - begin->x;
	delta_y = end->y - begin->y;
	begin->dp = 2 * delta_y - delta_x;
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

}
