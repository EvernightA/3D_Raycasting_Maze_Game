/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:11 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 13:17:29 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Set Up Your Laser Beam Direction! 🧭
 *
 * Imagine you're holding a flashlight and you want to point it in a specific
 * direction. This function tells your laser beam which way to go!
 *
 * It calculates:
 * - Which direction the beam should travel (using math with angles)
 * - Which grid square you're starting from (like "I'm in square 5,7")
 * - How far it needs to go to hit the next grid line in each direction
 *
 * The "large distance" trick is like saying "if you're going perfectly
 * straight, you won't hit any grid lines, so pretend the next one is
 * super far away!"
 *
 * @param ray Your laser beam that needs direction instructions
 * @param display Your game world with the player and map
 * @param angle How much to turn from straight ahead (like "turn 45 degrees right")
 */
void	init_ray_direction(t_ray *ray, t_display *display, float angle)
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

/**
 * @brief Plan Your Beam's First Steps! 🚶‍♂️
 *
 * Now that your laser knows which way it's going, it needs to figure out
 * how to start walking through the grid. This is like planning your first
 * few steps when you start a journey.
 *
 * The function checks:
 * - How far into the current square you are (like "I'm 3/4 of the way across")
 * - Which direction to step first (left/right or up/down)
 * - How far to the next grid line in each direction
 *
 * It's like a hiker checking their map and saying "First I need to walk
 * 2 more meters, then I'll hit the next trail marker!"
 *
 * @param ray Your laser beam with direction info
 * @param display Your game world with the player's position
 */
void	init_step_and_side_dist(t_ray *ray, t_display *display)
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

/**
 * @brief Check if You're Still on the Map! 🗺️
 *
 * Imagine you're exploring and you need to make sure you don't fall off
 * the edge of the world! This function checks if your laser beam is still
 * pointing at a valid part of the map.
 *
 * It makes sure:
 * - You're not above the top of the map
 * - You're not below the bottom of the map
 * - You're not left of the left edge
 * - You're not right of the right edge
 * - The square you're looking at actually exists
 *
 * It's like having a safety net that says "Don't go there - it's not safe!"
 *
 * @param ray Your laser beam showing which square it's checking
 * @param display Your game world with map boundaries
 * @return TRUE if the square is safe to look at, FALSE if it's off the map
 */
int	is_valid_map_pos(t_ray *ray, t_display *display)
{
	if (ray->map_y < 0 || ray->map_y >= display->texture.map_height)
		return (0);
	if (ray->map_x < 0 || ray->map_x >= display->texture.map_width)
		return (0);
	if (!display->map[ray->map_y][ray->map_x])
		return (0);
	return (1);
}

/**
 * @brief March Through the Grid Until You Hit a Wall! 🏃‍♀️
 *
 * This is the exciting part - your laser beam starts running through the grid
 * like a speedy explorer! It keeps jumping from one grid line to another
 * until it finds a wall to bounce off.
 *
 * At each step, it:
 * 1. Checks which direction is closer (left/right or up/down)
 * 2. Jumps to the next grid line in that direction
 * 3. Looks around and says "Is there a wall here?"
 * 4. If it finds a wall, it stops and celebrates!
 * 5. If it goes off the map, it stops too
 *
 * It's like playing tag in a giant checkerboard - keep running until
 * someone yells "You're it!" (or in this case, "Wall!")
 *
 * @param ray Your laser beam that will explore the grid
 * @param display Your game world with walls and open spaces
 */
void	perform_dda(t_ray *ray, t_display *display)
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

/**
 * @brief Measure Your Discovery and Plan the Wall Art! 📐
 *
 * Congratulations! Your laser found a wall. Now you need to:
 * 1. Measure exactly how far away it is (the "perpendicular distance")
 * 2. Figure out which direction the wall is facing (north/south/east/west)
 * 3. Calculate where on the wallpaper to look for the pattern
 *
 * The "perpendicular distance" is like measuring with a ruler held straight
 * out from you, not along the crooked laser path. This makes sure walls
 * look the right size no matter what angle you're looking from.
 *
 * The wall direction helps pick the right wallpaper, and wall_x tells you
 * "copy this part of the pattern here!"
 *
 * @param ray Your laser beam with all the discovery information
 * @param display Your game world with the player's position
 */
void	calculate_wall_dist_and_x(t_ray *ray, t_display *display)
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
