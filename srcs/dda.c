/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:26:52 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 14:29:46 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
