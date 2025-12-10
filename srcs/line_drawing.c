/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/10 14:10:51 by mratsima         ###   ########.fr       */
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

static float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static void	calc_hit_horizontal(t_hit *hit, t_display *display,
				float ray_dir[2], float bounds[4])
{
	float	wall_edge;
	float	t;
	float	min_y;
	float	max_y;
	float	min_x;
	float	max_x;

	if (hit->wall_direction == WEST)
		wall_edge = bounds[0];
	else
		wall_edge = bounds[1];
	hit->collision.f_x = wall_edge;
	if (fabsf(ray_dir[0]) > EPSILON)
	{
		t = (wall_edge - display->player.pixels.f_x) / ray_dir[0];
		hit->collision. f_y = display->player. pixels.f_y + ray_dir[1] * t;
		hit->collision.f_y = clamp(hit->collision.f_y, bounds[2], bounds[3]);
	}
	else
		hit->collision.f_y = display->player.pixels.f_y;
}

static void	calc_hit_vertical(t_hit *hit, t_display *display,
				float ray_dir[2], float bounds[4])
{
	float	wall_edge;
	float	t;

	if (hit->wall_direction == NORTH)
		wall_edge = bounds[2];
	else
		wall_edge = bounds[3];
	hit->collision. f_y = wall_edge;
	if (fabsf(ray_dir[1]) > EPSILON)
	{
		t = (wall_edge - display->player.pixels.f_y) / ray_dir[1];
		hit->collision.f_x = display->player.pixels.f_x + ray_dir[0] * t;
		hit->collision.f_x = clamp(hit->collision.f_x, bounds[0], bounds[1]);
	}
	else
		hit->collision.f_x = display->player. pixels.f_x;
}

static void	calc_exact_hit(t_hit *hit, t_display *display,
				float beta, t_point bloc)
{
	float	ray_dir[2];
	float	bounds[4];

	ray_dir[0] = cosf(display->player.angle + beta);
	ray_dir[1] = sinf(display->player.angle + beta);
	bounds[0] = bloc.x * SIZE_IMG;
	bounds[1] = (bloc.x + 1) * SIZE_IMG;
	bounds[2] = bloc.y * SIZE_IMG;
	bounds[3] = (bloc.y + 1) * SIZE_IMG;
	if (hit->wall_direction == WEST || hit->wall_direction == EAST)
		calc_hit_horizontal(hit, display, ray_dir, bounds);
	else
		calc_hit_vertical(hit, display, ray_dir, bounds);
}

void wall_assign(t_hit *hit, t_line *tmp, t_display *display, float beta, t_point bloc)
{
	hit->collision = tmp->dot;
	hit->wall_direction = get_wall_direction(hit->collision, display->player.blocs);
	direction_fix(display, hit, bloc);
	calc_exact_hit(hit, display, beta, bloc);
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
			break ;
		}
		display->beta = beta;
		if (go_to_next_node(&tmp, &before, &hit, display, bloc))
			break ;
	}
	return (hit);
}
