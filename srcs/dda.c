/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:26:52 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 13:31:02 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dda.c
 * @brief DDA (Digital Differential Analyzer) Algorithm Implementation 🌱
 *
 * This file contains functions for implementing the DDA line drawing algorithm,
 * which is used in raycasting to determine wall intersections. Think of it as
 * walking through a garden grid to find where you hit a flower bed (wall)!
 */

#include "../includes/cub.h"

/**
 * @brief DDA Line Drawing - Like Walking in a Grid Garden! 🌱
 *
 * Imagine you're in a big garden divided into square patches. You want to walk
 * from one flower (start point) to another flower (end point). But you can only
 * walk along the edges of the patches, like a grid.
 *
 * DDA (Digital Differential Analyzer) is like planning your walk:
 * - It figures out how many steps you need to take
 * - It calculates how much you move left/right (x_inc) and up/down (y_inc) each step
 * - It's like saying "for every 2 steps right, I need to take 1 step up"
 *
 * The function returns how many big steps you need, and how much to move each time.
 * If the start and end are the same spot, it just puts one flower there.
 */
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

/**
 * @brief Update Current Position - Taking a Step in Your Walk! 👣
 *
 * This is like stopping at each patch in the garden and remembering where you are.
 * It takes your current floating-point position (like 2.7, 3.2) and rounds it down
 * to whole numbers (like 2, 3) so you know which garden patch you're in.
 *
 * It's like saying "I'm at patch number 2 across and 3 up in the garden!"
 */
void	update_current(t_dda *dda)
{
	dda->current.f_x = dda->x;
	dda->current.f_y = dda->y;
	dda->current.x = (int)dda->x;
	dda->current.y = (int)dda->y;
	dda->current.dp = 0;
}

/**
 * @brief Initialize DDA - Getting Ready for Your Garden Walk! 🎒
 *
 * This is like packing your backpack before starting your walk:
 * - It figures out how far you need to go left/right (dx) and up/down (dy)
 * - It plans how many steps you'll take and how much to move each step
 * - It sets your starting position
 * - It gets your step counter ready (i = 0)
 *
 * If you don't need to move at all, it just says "you're already there!"
 */
int	initialize(t_dda *dda, t_point *begin, t_point *end)
{
	dda->head = NULL;
	dda->tail = NULL;
	dda->dx = end->f_x - begin->f_x;
	dda->dy = end->f_y - begin->f_y;
	if (!calculate_steps_and_increment(dda, begin))
		return (0);
	dda->x = begin->f_x;
	dda->y = begin->f_y;
	dda->i = 0;
	return (1);
}

/**
 * @brief DDA Line Drawing - Walking Through the Garden! 🚶‍♀️
 *
 * This is the main walking function! You start at your first flower and take
 * small steps until you reach the second flower. At each step, you:
 * 1. Remember where you are (update_current)
 * 2. Add a new point to your path (like leaving breadcrumbs)
 * 3. Move a little bit left/right and up/down
 * 4. Count your step
 *
 * It's like walking from one flower to another, stopping at every patch
 * along the way to make a dotted line path through the garden!
 *
 * The function returns a linked list of all the points you visited.
 */
t_line	*dda_line(t_point *begin, t_point *end)
{
	t_dda	dda;

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
