/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/13 15:38:44 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	calculate_wall_dist_and_x(t_display *display)
{
	if (display->ray.side == 0)
	{
		display->ray.perp_wall_dist = display->ray.side_dist_x
			- display->ray.delta_dist_x;
		display->ray.wall_x = display->player.pixels.f_y / SIZE_IMG
			+ display->ray.perp_wall_dist * display->ray.dir_y;
		if (display->ray.step_x > 0)
			display->ray.wall_dir = WEST;
		else
			display->ray.wall_dir = EAST;
	}
	else
	{
		display->ray.perp_wall_dist = display->ray.side_dist_y
			- display->ray.delta_dist_y;
		display->ray.wall_x = display->player.pixels.f_x / SIZE_IMG
			+ display->ray.perp_wall_dist * display->ray.dir_x;
		if (display->ray.step_y > 0)
			display->ray.wall_dir = NORTH;
		else
			display->ray.wall_dir = SOUTH;
	}
	display->ray.wall_x -= floorf(display->ray.wall_x);
	display->ray.perp_wall_dist *= cosf(display->ray.angle_offset);
}

void	wall_assign(t_hit *hit, t_display *display)
{
	calculate_wall_dist_and_x(display);
	hit->wall_direction = display->ray.wall_dir;
	hit->distance = display->ray.perp_wall_dist;
	hit->collision = display->ray.wall_x;
}

int	go_to_next_node(t_line **tmp, t_line **before, t_hit *hit,
		t_display *display)
{
	if ((*tmp)->next == NULL)
	{
		*before = *tmp;
		wall_assign(hit, display);
		return (1);
	}
	*tmp = (*tmp)->next;
	return (0);
}

int	is_walkable(t_display *display, t_point tmp_bloc)
{
	return (display->map[tmp_bloc.y][tmp_bloc.x] == '0'
		|| is_player(display->map[tmp_bloc.y][tmp_bloc.x]));
}

t_hit	draw_line(t_display *display, float beta)
{
	t_line	*tmp;
	t_line	*before;
	t_point	tmp_bloc;
	t_hit	hit;

	tmp = display->head;
	before = NULL;
	hit.collision = 0;
	hit.distance = 0;
	hit.wall_direction = 0;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (!is_walkable(display, tmp_bloc))
		{
			wall_assign(&hit, display);
			break ;
		}
		display->beta = beta;
		if (go_to_next_node(&tmp, &before, &hit, display))
			break ;
	}
	return (hit);
}
