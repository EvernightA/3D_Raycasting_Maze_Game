/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/10 10:18:59 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_hit(t_hit *hit)
{
	hit->distance = 0;
	hit->collision.x = 0;
	hit->collision.y = 0;
	hit->collision.f_x = 0;
	hit->collision.f_y = 0;
}

#define EPSILON 1e-6f

static void	calc_exact_hit(t_hit *hit, t_display *display, float beta)
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	wall_edge;
	float	t;

	ray_dir_x = cosf(display->player.angle + beta);
	ray_dir_y = sinf(display->player.angle + beta);
	if (hit->wall_direction == WEST && fabsf(ray_dir_x) > EPSILON)
	{
		wall_edge = (hit->collision.x / SIZE_IMG) * SIZE_IMG;
		t = (wall_edge - display->player.pixels.f_x) / ray_dir_x;
		hit->collision.f_x = wall_edge;
		hit->collision.f_y = display->player.pixels.f_y + ray_dir_y * t;
	}
	else if (hit->wall_direction == EAST && fabsf(ray_dir_x) > EPSILON)
	{
		wall_edge = (hit->collision.x / SIZE_IMG + 1) * SIZE_IMG;
		t = (wall_edge - display->player.pixels.f_x) / ray_dir_x;
		hit->collision.f_x = wall_edge;
		hit->collision.f_y = display->player.pixels.f_y + ray_dir_y * t;
	}
	else if (hit->wall_direction == NORTH && fabsf(ray_dir_y) > EPSILON)
	{
		wall_edge = (hit->collision.y / SIZE_IMG) * SIZE_IMG;
		t = (wall_edge - display->player.pixels.f_y) / ray_dir_y;
		hit->collision.f_x = display->player.pixels.f_x + ray_dir_x * t;
		hit->collision.f_y = wall_edge;
	}
	else if (hit->wall_direction == SOUTH && fabsf(ray_dir_y) > EPSILON)
	{
		wall_edge = (hit->collision.y / SIZE_IMG + 1) * SIZE_IMG;
		t = (wall_edge - display->player.pixels.f_y) / ray_dir_y;
		hit->collision.f_x = display->player.pixels.f_x + ray_dir_x * t;
		hit->collision.f_y = wall_edge;
	}
}

void wall_assign(t_hit *hit, t_line *tmp, t_display *display, float beta, t_point bloc)
{
	hit->collision = tmp->dot;
	hit->wall_direction = get_wall_direction(hit->collision, display->player.blocs);
	direction_fix(display, hit, bloc);
	calc_exact_hit(hit, display, beta);
	hit->distance = to_wall(display, hit->collision, beta);
}

int	go_to_next_node(t_line **tmp, t_line **before, t_hit *hit,
		t_display *display, t_point bloc)
{
	if ((*tmp)->next == NULL)
	{
		*before = *tmp;
		wall_assign(hit, *before, display, display->beta, bloc);
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

t_hit	draw_line_2(t_display *display, float beta)
{
	t_line	*tmp;
	t_line	*before;
	t_point	tmp_bloc;
	t_hit	hit;
	t_point	bloc;

	tmp = display->head;
	before = NULL;
	init_hit(&hit);
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		bloc = tmp_bloc;
		if (!is_walkable(display, tmp_bloc))
		{
			wall_assign(&hit, tmp, display, beta, bloc);
			// direction_fix(display, &hit, bloc);
			break ;
		}
		display->beta = beta;
		if (go_to_next_node(&tmp, &before, &hit, display, bloc))
			break ;
	}
	return (hit);
}
