/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/24 18:54:31 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_point calculate_end(t_point begin, float angle, int max_distance)
{
	// angle deja en radian
	/*
	Formule de deplacement

	déplacement_horizontal (Δx) = cos(θ) × d
	déplacement_vertical   (Δy) = sin(θ) × d
	
	C'est comme un calcul pour l'orientation
	*/
	t_point end;
	
	end.x = begin.x + cos(angle) * max_distance;
	end.y = begin.y + sin(angle) * max_distance; 
	
// A corriger

	return (end);
}

void draw_wall_lines(t_display *display, t_hit hit, int pixel_index, float angle)
{
	t_line *line;
	int line_size;
	t_point begin;
	t_point end;
	
	(void)angle;
	/*How we calculate the distance may be the problem ?*/
	if (hit.distance)
		line_size =  SIZE_IMG * WALL_UNIT / hit.distance;
	else
	{
		line_size = SCRN_HEIGHT;
		printf("=====================================================> %f\n", hit.distance);
	}
	begin.y = (SCRN_HEIGHT >> 1) - (line_size >> 1);
	begin.x = pixel_index;
	end.x = pixel_index;
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

void	cast_ray(t_point begin,t_display *display, int d)
{
	float	angle;
	int		pixel_index;
	t_hit	hit;

	(void)d;
	(void)begin;
	pixel_index = 0;
	angle = -FOV / 2;
	while (angle <= FOV / 2)
	{
		hit = cast_ray_dda(display, display->player.angle + angle);
		draw_wall_lines(display, hit, pixel_index, angle);
		angle += (FOV / SCRN_WIDTH);
		pixel_index++;
	}
}

//int delta_x;
//int delta_y;
//int x_step;
//int y_step;
//int err;
//int dp;

t_line	*bresenham_line(t_point *begin, t_point *end)
{
	t_bres	utils;
	t_point current;
	t_line *head;
	t_line *new_node;
	t_line	*tail;
	
	head = NULL;
	tail = NULL;
	utils.delta_x = ft_abs(end->x - begin->x);
	utils.delta_y = ft_abs(end->y - begin->y);
	if ((begin->x < end->x))
		utils.x_step = 1;
	else
		utils.x_step = -1;
	if ((begin->y < end->y))
		utils.y_step = 1;
	else
		utils.y_step = -1;
	utils.err = utils.delta_x - utils.delta_y;
	current = *begin;
	while (1)
	{
		new_node = ft_linenew(current);
		//ft_lineadd_back(&head, new_node);
		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		if (current.x == end->x && current.y == end->y)
			break ;
		utils.dp = 2 * utils.err;
		if (utils.dp > -utils.delta_y)
		{
			utils.err -= utils.delta_y;
			current.x += utils.x_step;
		}
		if (utils.dp < utils.delta_x)
		{
			utils.err += utils.delta_x;
			current.y += utils.y_step;
		}
		//mlx_pixel_put();
	}
	return (head);
}