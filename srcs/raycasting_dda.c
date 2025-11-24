/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:00 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/24 16:44:00 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_hit	cast_ray_dda(t_display *display, float ray_angle)
{
	t_hit	hit;
	float	ray_dir_x;
	float	ray_dir_y;
	float	pos_x;
	float	pos_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit_wall;
	int		side;
	float	perp_wall_dist;

	ray_dir_x = cosf(ray_angle);
	ray_dir_y = sinf(ray_angle);
	pos_x = (float)display->player.pixels.x;
	pos_y = (float)display->player.pixels.y;
	map_x = display->player.blocs.x;
	map_y = display->player.blocs.y;
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabsf(1 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabsf(1 / ray_dir_y);
	hit_wall = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x / SIZE_IMG - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x / SIZE_IMG) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y / SIZE_IMG - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y / SIZE_IMG) * delta_dist_y;
	}
	while (hit_wall == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_y < 0 || map_y >= display->texture.map_height
			|| map_x < 0 || map_x >= display->texture.map_width)
		{
			hit_wall = 1;
		}
		else if (!display->map[map_y][map_x]
			|| display->map[map_y][map_x] == '1')
		{
			hit_wall = 1;
		}
	}
	if (side == 0)
		perp_wall_dist = (side_dist_x - delta_dist_x);
	else
		perp_wall_dist = (side_dist_y - delta_dist_y);
	hit.distance = perp_wall_dist * SIZE_IMG;
	if (side == 0)
	{
		hit.collision_precise.x = map_x * SIZE_IMG + (step_x > 0 ? 0 : SIZE_IMG);
		hit.collision_precise.y = pos_y + perp_wall_dist * ray_dir_y * SIZE_IMG;
	}
	else
	{
		hit.collision_precise.x = pos_x + perp_wall_dist * ray_dir_x * SIZE_IMG;
		hit.collision_precise.y = map_y * SIZE_IMG + (step_y > 0 ? 0 : SIZE_IMG);
	}
	hit.collision.x = (int)hit.collision_precise.x;
	hit.collision.y = (int)hit.collision_precise.y;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			hit.wall_direction = WEST;
		else
			hit.wall_direction = EAST;
	}
	else
	{
		if (ray_dir_y > 0)
			hit.wall_direction = NORTH;
		else
			hit.wall_direction = SOUTH;
	}
	return (hit);
}
