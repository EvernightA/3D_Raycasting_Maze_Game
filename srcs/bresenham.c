/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/01 09:39:51 by fsamy-an         ###   ########.fr       */
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
	end.f_x = begin.f_x + cos(angle) * max_distance;
	end.f_y = begin.f_y + sin(angle) * max_distance;
	
	return (end);
}

void draw_wall_lines(t_display *display, t_hit hit, int pixel_index, float angle)
{
	t_line *line;
	int line_size;
	t_point begin;
	t_point end;
	
	(void)angle;
	if (hit.distance)
		line_size =  SIZE_IMG * WALL_UNIT / hit.distance;
	else
		line_size = SCRN_HEIGHT;
	begin.y = (SCRN_HEIGHT >> 1) - (line_size >> 1);
	begin.x = pixel_index;
	end.x = pixel_index;
	begin.f_x = pixel_index;
	end.f_x = pixel_index;
	begin.f_y = (SCRN_HEIGHT >> 1) - (line_size >> 1);
	end.y = (SCRN_HEIGHT >> 1) + (line_size >> 1);
	end.f_y = (SCRN_HEIGHT >> 1) + (line_size >> 1);
	line = dda_line(&begin, &end);
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
	t_point true_end;
	float	angle;
	int pixel_index;
	// float distance;
	t_hit hit;

	/*
		Dans cette fonction nous mettons angle = -FOV/2 pour que la direction principale se trouve au milieu
	*/
	/*PIXEL INDEX IS USED TO TRACK WHICH SCREEN LINE WE SHOULD DRAW*/
	pixel_index = 0;
	angle = -FOV / 2;
	while (angle <= FOV / 2)
	{
		true_end = calculate_end(begin, display->player.angle + angle, d);
		/*
			Nous avons ajouter l'orientation duplayer a l'angle pour dessiner des rayons dans ltes cotes environnants
			Notons que player.angle est update a chaque fois que Left ou right est presEE


			Ex :

			itereation 1:

			player_angle = 0;
			angle = -MPI / 3;
			
			calcule de end pour l'angle new = 0 - MPI/3;
			On cree une ligne grace a bresenham pour new
			On dessine la ligne

			On fait ca pour chaque iteration
		*/

		if (display->head)
			ft_linefree(&display->head);
		display->head = dda_line(&begin, &true_end);
		hit = draw_line_2(display, angle); // This draw line uses yellow
		if (display->head)
		{
			ft_linefree(&display->head);
			display->head = NULL;
		}
		draw_wall_lines(display, hit, pixel_index, angle);
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
