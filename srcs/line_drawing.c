/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/09 18:42:51 by mratsima         ###   ########.fr       */
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

void	wall_assign(t_hit *hit, t_line *tmp, t_display *display, float beta)
{
	hit->collision = tmp->dot;
	hit->distance = to_wall(display, tmp->dot, beta);
	hit->wall_direction = get_wall_direction(hit->collision,
			display->player.blocs);
}

int	go_to_next_node(t_line **tmp, t_line **before, t_hit *hit,
		t_display *display)
{
	if ((*tmp)->next == NULL)
	{
		*before = *tmp;
		wall_assign(hit, *before, display, display->beta);
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
		if (!is_walkable(display, tmp_bloc))
		{
			wall_assign(&hit, tmp, display, beta);
			direction_fix(display, &hit, bloc);
			break ;
		}
		display->beta = beta;
		if (go_to_next_node(&tmp, &before, &hit, display))
			break ;
	}
	return (hit);
}
