/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:26:52 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 14:13:42 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// int	calculate_steps_and_increment(t_dda *dda, t_point *begin)
// {
// 	if (fabsf(dda->dx) > fabsf(dda->dy))
// 		dda->steps = fabsf(dda->dx);
// 	else
// 		dda->steps = fabsf(dda->dy);
// 	if (dda->steps == 0)
// 	{
// 		dda->new_node = ft_linenew(*begin);
// 		return (0);
// 	}
// 	dda->x_inc = dda->dx / dda->steps;
// 	dda->y_inc = dda->dy / dda->steps;
// 	return (1);
// }

// void	update_current(t_dda *dda)
// {
// 	dda->current.f_x = dda->x;
// 	dda->current.f_y = dda->y;
// 	dda->current.x = (int)dda->x;
// 	dda->current.y = (int)dda->y;
// 	dda->current.dp = 0;
// }

// int	initialize(t_dda *dda, t_point *begin, t_point *end)
// {
// 	dda->head = NULL;
// 	dda->tail = NULL;
// 	dda->dx = end->f_x - begin->f_x;
// 	dda->dy = end->f_y - begin->f_y;
// 	if (!calculate_steps_and_increment(dda, begin))
// 		return (0);
// 	dda->x = begin->f_x;
// 	dda->y = begin->f_y;
// 	dda->i = 0;
// 	return (1);
// }

// t_line	*dda_line(t_point *begin, t_point *end)
// {
// 	t_dda	dda;

// 	if (!initialize(&dda, begin, end))
// 		return (0);
// 	while (dda.i <= (int)dda.steps)
// 	{
// 		update_current(&dda);
// 		dda.new_node = ft_linenew(dda.current);
// 		if (dda.head == NULL)
// 		{
// 			dda.head = dda.new_node;
// 			dda.tail = dda.new_node;
// 		}
// 		else
// 		{
// 			dda.tail->next = dda.new_node;
// 			dda.tail = dda.new_node;
// 		}
// 		dda.x += dda.x_inc;
// 		dda.y += dda.y_inc;
// 		dda.i++;
// 	}
// 	return (dda.head);
// }

int	is_valid_map_pos(t_display *display)
{
	if (display->ray.map_y < 0 || display->ray.map_y >= display->texture.map_height)
		return (0);
	if (display->ray.map_x < 0 || display->ray.map_x >= display->texture.map_width)
		return (0);
	if (!display->map[display->ray.map_y][display->ray.map_x])
		return (0);
	return (1);
}

void	init_ray_direction(t_display *display, float angle)
{
	display->ray.angle_offset = angle;
	display->ray.dir_x = cosf(display->player.angle + angle);
	display->ray.dir_y = sinf(display->player.angle + angle);
	display->ray.map_x = (int)(display->player.pixels.f_x / SIZE_IMG);
	display->ray.map_y = (int)(display->player.pixels.f_y / SIZE_IMG);
	if (display->ray.dir_x == 0)
		display->ray.delta_dist_x = LARGE_DIST;
	else
		display->ray.delta_dist_x = fabsf(1.0f / display->ray.dir_x);
	if (display->ray.dir_y == 0)
		display->ray.delta_dist_y = LARGE_DIST;
	else
		display->ray.delta_dist_y = fabsf(1.0f / display->ray.dir_y);
}

void	init_step_and_side_dist(t_display *display)
{
	float	pos_in_cell_x;
	float	pos_in_cell_y;

	pos_in_cell_x = display->player.pixels.f_x / SIZE_IMG - display->ray.map_x;
	pos_in_cell_y = display->player.pixels.f_y / SIZE_IMG - display->ray.map_y;
	if (display->ray.dir_x < 0)
	{
		display->ray.step_x = -1;
		display->ray.side_dist_x = pos_in_cell_x * display->ray.delta_dist_x;
	}
	else
	{
		display->ray.step_x = 1;
		display->ray.side_dist_x = (1.0f - pos_in_cell_x) * display->ray.delta_dist_x;
	}
	if (display->ray.dir_y < 0)
	{
		display->ray.step_y = -1;
		display->ray.side_dist_y = pos_in_cell_y * display->ray.delta_dist_y;
	}
	else
	{
		display->ray.step_y = 1;
		display->ray.side_dist_y = (1.0f - pos_in_cell_y) * display->ray.delta_dist_y;
	}
}

t_line	*dda_line(t_display *display)
{
	int	hit;
	t_dda dda;

	hit = 0;
	dda.head = NULL;
	dda.tail = NULL;
	while (hit == 0)
	{
		if (display->ray.side_dist_x < display->ray.side_dist_y)
		{
			display->ray.side_dist_x += display->ray.delta_dist_x;
			display->ray.map_x += display->ray.step_x;
			display->ray.side = 0;
		}
		else
		{
			display->ray.side_dist_y += display->ray.delta_dist_y;
			display->ray.map_y += display->ray.step_y;
			display->ray.side = 1;
		}
		dda.current.x = display->ray.map_x;
		dda.current.y = display->ray.map_y;
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
		if (is_valid_map_pos(display))
		{
			if (display->map[display->ray.map_y][display->ray.map_x] == '1')
				hit = 1;
		}
		else
			hit = 1;
	}
	dda.new_node = NULL;
	dda.tail = dda.new_node;
	return (dda.head);
}
