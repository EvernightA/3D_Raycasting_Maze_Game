/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/13 14:33:48 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_wall_lines(t_display *display, t_hit hit, int pixel_index)
{
	t_line	*line;
	int		line_size;
	t_point	begin;
	t_point	end;

	if (hit.distance)
		line_size = SCRN_HEIGHT / hit.distance;
	else
		line_size = SCRN_HEIGHT;
	begin.y = (SCRN_HEIGHT >> 1) - (line_size >> 1);
	begin.x = pixel_index;
	end.x = pixel_index;
	begin.f_x = pixel_index;
	end.f_x = pixel_index;
	end.y = (SCRN_HEIGHT >> 1) + (line_size >> 1);
	line = bresenham_line(&begin, &end);
	draw_textured_line(line, hit, line_size, display);
	ft_linefree(&line);
	if (display->head)
	{
		ft_linefree(&display->head);
		display->head = NULL;
	}
}

void	cast_ray(t_display *display)
{
	t_hit	hit;
	float	angle;
	int		pixel_index;

	pixel_index = 0;
	angle = -FOV / 2;
	while (angle <= FOV / 2)
	{
		init_ray_direction(display, angle);
		init_step_and_side_dist(display);
		if (display->head)
			ft_linefree(&display->head);
		display->head = dda_line(display);
		hit = draw_line(display, angle);
		if (display->head)
		{
			ft_linefree(&display->head);
			display->head = NULL;
		}
		draw_wall_lines(display, hit, pixel_index);
		angle += (FOV / SCRN_WIDTH);
		pixel_index++;
	}
}

void	initialize_bres(t_bres *bres, t_point *begin, t_point *end)
{
	bres->head = NULL;
	bres->tail = NULL;
	bres->delta_x = ft_abs(end->x - begin->x);
	bres->delta_y = ft_abs(end->y - begin->y);
	if ((begin->x < end->x))
		bres->x_step = 1;
	else
		bres->x_step = -1;
	if ((begin->y < end->y))
		bres->y_step = 1;
	else
		bres->y_step = -1;
	bres->err = bres->delta_x - bres->delta_y;
	bres->current = *begin;
}

void	increment_bres(t_bres *bres)
{
	bres->dp = 2 * bres->err;
	if (bres->dp > -bres->delta_y)
	{
		bres->err -= bres->delta_y;
		bres->current.x += bres->x_step;
	}
	if (bres->dp < bres->delta_x)
	{
		bres->err += bres->delta_x;
		bres->current.y += bres->y_step;
	}
}

t_line	*bresenham_line(t_point *begin, t_point *end)
{
	t_bres	bres;

	initialize_bres(&bres, begin, end);
	while (1)
	{
		bres.new_node = ft_linenew(bres.current);
		if (bres.head == NULL)
		{
			bres.head = bres.new_node;
			bres.tail = bres.new_node;
		}
		else
		{
			bres.tail->next = bres.new_node;
			bres.tail = bres.new_node;
		}
		if (bres.current.x == end->x && bres.current.y == end->y)
			break ;
		increment_bres(&bres);
	}
	return (bres.head);
}
