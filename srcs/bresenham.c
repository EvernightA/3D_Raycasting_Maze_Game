/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/12 13:17:30 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Initialize Bresenham - Setting Up Your Pixel Path! 🏁
 *
 * Imagine you want to draw a straight line on a checkerboard (your computer screen).
 * Bresenham's algorithm is like a smart way to decide which squares to color in.
 *
 * This setup function is like getting your coloring tools ready:
 * - It figures out how far you need to go left/right (delta_x) and up/down (delta_y)
 * - It decides which way to step: right/left (+1 or -1) for x, up/down (+1 or -1) for y
 * - It starts an "error counter" that helps decide when to move diagonally
 * - It puts you at the starting square
 *
 * Think of it like planning a treasure hunt across the checkerboard!
 */
void	initialize_bres(t_bres *bres, t_point *begin, t_point *end)
{
	bres->head = NULL;
	bres->tail = NULL;
	bres->delta_x = ft_abs(end->x - begin->x);
	bres->delta_y = ft_abs(end->y - begin->y);
	if ((begin->x < end->x))
		bres->x_step = 1;
	else
		bres->x_step = -1;
	if ((begin->y < end->y))
		bres->y_step = 1;
	else
		bres->y_step = -1;
	bres->err = bres->delta_x - bres->delta_y;
	bres->current = *begin;
}

/**
 * @brief Take a Step in Bresenham - Choosing Your Next Square! 🎯
 *
 * This is the smart part! When drawing a line, sometimes you need to go straight,
 * sometimes diagonally. The "error counter" helps decide:
 *
 * Imagine you're walking and carrying a backpack. Every time you take a step,
 * you check how heavy your backpack feels (that's the error). If it's too heavy
 * on one side, you adjust by stepping in that direction.
 *
 * - If the error is big on the x-side, you step left/right
 * - If the error is big on the y-side, you step up/down
 * - This keeps your line as straight as possible!
 *
 * It's like balancing on a tightrope - you make small adjustments to stay straight.
 */
void	increment_bres(t_bres *bres)
{
	bres->dp = 2 * bres->err;
	if (bres->dp > -bres->delta_y)
	{
		bres->err -= bres->delta_y;
		bres->current.x += bres->x_step;
	}
	if (bres->dp < bres->delta_x)
	{
		bres->err += bres->delta_x;
		bres->current.y += bres->y_step;
	}
}

/**
 * @brief Bresenham Line Drawing - Connecting the Dots! ✏️
 *
 * This is like playing connect-the-dots, but the computer does it automatically!
 * You start at your first dot and keep coloring squares until you reach the last dot.
 *
 * At each square, you:
 * 1. Color it in (add it to your path)
 * 2. Check if you're at the end (like "are we there yet?")
 * 3. If not, take a smart step to the next square using increment_bres
 *
 * It's like having a robot that draws perfect straight lines by carefully
 * choosing which pixels to light up on your screen!
 *
 * The function returns a chain of all the colored squares (a linked list).
 */
t_line	*bresenham_line(t_point *begin, t_point *end)
{
	t_bres	bres;

	initialize_bres(&bres, begin, end);
	while (1)
	{
		bres.new_node = ft_linenew(bres.current);
		if (bres.head == NULL)
		{
			bres.head = bres.new_node;
			bres.tail = bres.new_node;
		}
		else
		{
			bres.tail->next = bres.new_node;
			bres.tail = bres.new_node;
		}
		if (bres.current.x == end->x && bres.current.y == end->y)
			break ;
		increment_bres(&bres);
	}
	return (bres.head);
}
