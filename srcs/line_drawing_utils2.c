/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:18:58 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 13:17:29 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Cast a Single Ray - Shoot Your Laser Pointer! 🔦
 *
 * Imagine you have a magic laser pointer that shoots out from your eyes
 * and tells you where the walls are. This function shoots just ONE laser
 * beam in a specific direction and figures out exactly where it hits a wall.
 *
 * The laser beam:
 * 1. Knows which way it's pointing (angle_offset)
 * 2. Gets ready to travel (init_ray_direction)
 * 3. Plans its path through the grid (init_step_and_side_dist)
 * 4. Actually travels until it hits something (perform_dda)
 * 5. Measures how far it went and what it hit (calculate_wall_dist_and_x)
 *
 * It's like having a treasure hunter that explores one path at a time,
 * mapping out your 3D world with laser precision!
 *
 * @param display Your whole 3D world with walls and floors
 * @param ray Your laser beam that will explore and report back
 * @param angle Which direction to point the laser (like "30 degrees to the right")
 */
void	cast_single_ray(t_display *display, t_ray *ray, float angle)
{
	ray->angle_offset = angle;
	init_ray_direction(ray, display, angle);
	init_step_and_side_dist(ray, display);
	perform_dda(ray, display);
	calculate_wall_dist_and_x(ray, display);
}
