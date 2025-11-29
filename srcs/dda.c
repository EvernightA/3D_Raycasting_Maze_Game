/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:26:52 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/29 09:58:27 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	calculate_steps_and_increment(t_dda *dda, t_point *begin)
{
	if (fabsf(dda->dx) > fabsf(dda->dy))
		dda->steps = fabsf(dda->dx);
	else
		dda->steps = fabsf(dda->dy);
	if (dda->steps == 0)
	{
		dda->new_node = ft_linenew(*begin);
		return (0);
	}
	dda->x_inc = dda->dx / dda->steps;
	dda->y_inc = dda->dy / dda->steps;
	return (1);
}

void	update_current(t_dda *dda)
{
	dda->current.f_x = dda->x;
	dda->current.f_y = dda->y;
	dda->current.x = (int)dda->x;
	dda->current.y = (int)dda->y;
	dda->current.dp = 0;
}

int initialize(t_dda *dda, t_point *begin, t_point *end)
{
	dda->head = NULL;
	dda->tail = NULL;
	// Use the precise coordinates for calculation
	dda->dx = end->f_x - begin->f_x;
	dda->dy = end->f_y - begin->f_y;
	if (!calculate_steps_and_increment(dda, begin))
		return (0);
	dda->x = begin->f_x;
	dda->y = begin->f_y;
	dda->i = 0;
	return (1);
}

t_line	*dda_line(t_point *begin, t_point *end)
{
	t_dda dda;

	if (!initialize(&dda, begin, end))
		return (0);
	while (dda.i <= (int)dda.steps)
	{
		update_current(&dda);
		dda.new_node = ft_linenew(dda.current);
		if (dda.head == NULL)
		{
			dda.head = dda.new_node;
			dda.tail = dda.new_node;
		}
		else
		{
			dda.tail->next = dda.new_node;
			dda.tail = dda.new_node;
		}
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
		dda.i++;
	}
	return (dda.head);
}
