/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/25 10:39:07 by mratsima         ###   ########.fr       */
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
	// if (line_size > SCRN_HEIGHT * 2)
 	//    line_size = SCRN_HEIGHT * 2;  // fix for the fisheye close
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

t_line	*dda_line(t_point *begin, t_point *end)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;
	t_point	current;
	t_line	*head;
	t_line	*new_node;
	t_line	*tail;
	
	head = NULL;
	tail = NULL;
	
	// Use the precise coordinates for calculation
	dx = end->f_x - begin->f_x;
	dy = end->f_y - begin->f_y;
	
	// Calculate steps - take the larger absolute value
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	
	// Avoid division by zero
	if (steps == 0)
	{
		new_node = ft_linenew(*begin);
		return (new_node);
	}
	
	// Calculate increment for each step
	x_inc = dx / steps;
	y_inc = dy / steps;
	
	// Start at beginning point
	x = begin->f_x;
	y = begin->f_y;
	
	i = 0;
	while (i <= (int)steps)
	{
		// Store both integer and float versions
		current.f_x = x;
		current.f_y = y;
		current.x = (int)x;  // Just truncate - no rounding!
		current.y = (int)y;  // Just truncate - no rounding!
		current.dp = 0;
		
		new_node = ft_linenew(current);
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
		
		x += x_inc;
		y += y_inc;
		i++;
	}
	
	return (head);
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