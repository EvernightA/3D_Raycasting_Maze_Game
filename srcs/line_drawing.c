/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	init_ray_direction(t_ray *ray, t_display *display, float angle)
{
	ray->dir_x = cosf(display->player.angle + angle);
	ray->dir_y = sinf(display->player.angle + angle);
	ray->map_x = (int)(display->player.pixels.f_x / SIZE_IMG);
	ray->map_y = (int)(display->player.pixels.f_y / SIZE_IMG);
	if (ray->dir_x == 0)
		ray->delta_dist_x = LARGE_DIST;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = LARGE_DIST;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->dir_y);
}

static void	init_step_and_side_dist(t_ray *ray, t_display *display)
{
	float	pos_in_cell_x;
	float	pos_in_cell_y;

	pos_in_cell_x = display->player.pixels.f_x / SIZE_IMG - ray->map_x;
	pos_in_cell_y = display->player.pixels.f_y / SIZE_IMG - ray->map_y;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = pos_in_cell_x * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (1.0f - pos_in_cell_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = pos_in_cell_y * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (1.0f - pos_in_cell_y) * ray->delta_dist_y;
	}
}

static int	is_valid_map_pos(t_ray *ray, t_display *display)
{
	if (ray->map_y < 0 || ray->map_y >= display->texture.map_height)
		return (0);
	if (ray->map_x < 0 || ray->map_x >= display->texture.map_width)
		return (0);
	if (!display->map[ray->map_y][ray->map_x])
		return (0);
	return (1);
}

static void	perform_dda(t_ray *ray, t_display *display)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_valid_map_pos(ray, display))
		{
			if (display->map[ray->map_y][ray->map_x] == '1')
				hit = 1;
		}
		else
			hit = 1;
	}
}

/*
** Calculate perpendicular wall distance and texture x coordinate.
** Wall direction logic:
** - When ray hits a vertical wall (side == 0):
**   - step_x > 0: ray moves right, hits WEST face of wall cell
**   - step_x < 0: ray moves left, hits EAST face of wall cell
** - When ray hits a horizontal wall (side == 1):
**   - step_y > 0: ray moves down, hits NORTH face of wall cell
**   - step_y < 0: ray moves up, hits SOUTH face of wall cell
*/
static void	calculate_wall_dist_and_x(t_ray *ray, t_display *display)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
		ray->wall_x = display->player.pixels.f_y / SIZE_IMG
			+ ray->perp_wall_dist * ray->dir_y;
		if (ray->step_x > 0)
			ray->wall_dir = WEST;
		else
			ray->wall_dir = EAST;
	}
	else
	{
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
		ray->wall_x = display->player.pixels.f_x / SIZE_IMG
			+ ray->perp_wall_dist * ray->dir_x;
		if (ray->step_y > 0)
			ray->wall_dir = NORTH;
		else
			ray->wall_dir = SOUTH;
	}
	ray->wall_x -= floorf(ray->wall_x);
}

void	cast_single_ray(t_display *display, t_ray *ray, float angle)
{
	init_ray_direction(ray, display, angle);
	init_step_and_side_dist(ray, display);
	perform_dda(ray, display);
	calculate_wall_dist_and_x(ray, display);
}
