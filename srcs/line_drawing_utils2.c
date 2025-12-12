/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:18:58 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 11:19:41 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	cast_single_ray(t_display *display, t_ray *ray, float angle)
{
	ray->angle_offset = angle;
	init_ray_direction(ray, display, angle);
	init_step_and_side_dist(ray, display);
	perform_dda(ray, display);
	calculate_wall_dist_and_x(ray, display);
}
