/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:26:52 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/29 09:32:22 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_line	*dda_line(t_point *begin, t_point *end)
{
	t_dda dda;
	
	dda.head = NULL;
	dda.tail = NULL;
	
	// Use the precise coordinates for calculation
	dda.dx = end->f_x - begin->f_x;
	dda.dy = end->f_y - begin->f_y;
	
	// Calculate dda.steps - take the larger absolute value
	if (fabsf(dda.dx) > fabsf(dda.dy))
		dda.steps = fabsf(dda.dx);
	else
		dda.steps = fabsf(dda.dy);
	
	// Avoid division by zero
	if (dda.steps == 0)
	{
		dda.new_node = ft_linenew(*begin);
		return (dda.new_node);
	}
	
	// Calculate increment for each step
	dda.x_inc = dda.dx / dda.steps;
	dda.y_inc = dda.dy / dda.steps;
	
	// Start at beginning point
	dda.x = begin->f_x;
	dda.y = begin->f_y;
	
	dda.i = 0;
	while (dda.i <= (int)dda.steps)
	{
		// Store both integer and float versions
		dda.current.f_x = dda.x;
		dda.current.f_y = dda.y;
		dda.current.x = (int)dda.x;  // Just truncate - no rounding!
		dda.current.y = (int)dda.y;  // Just truncate - no rounding!
		dda.current.dp = 0;
		
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
