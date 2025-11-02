/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/02 08:44:23 by mratsima         ###   ########.fr       */
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
	return (end);
}

void draw_wall_lines(t_display *display, int distance, int pixel_index)
{
	t_line *line;
	int line_size;
	t_point begin;
	t_point end;

	if (distance)
		line_size = SIZE_IMG / distance;
	begin.y = SCRN_HEIGHT/2 - line_size/2;
	begin.x = pixel_index;
	end.x = pixel_index;
	end.y = SCRN_HEIGHT/2 + line_size/2;
	line = bresenham_line(&begin, &end);
	draw_simple_line2(line, display);
}

void	cast_ray(t_point begin,t_display *display, int d)
{
	t_point true_end;
	float	angle;
	int pixel_index;
	int distance;

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
		display->head = bresenham_line(&begin, &true_end);
		distance = draw_line_2(display); // This draw line uses yellow
		draw_wall_lines(display, distance, pixel_index);
		angle += FOV / SCRN_WIDTH;
		pixel_index++;
	}
}

void	ray_fov(t_point begin,t_display *display, int d)
{
	//int	i;
	float tmp_angle;
	t_point end;

	//i = 0;
	tmp_angle = FOV;
	while (tmp_angle > 0)
	{
		end = calculate_end(begin, tmp_angle, d);
		display->head = bresenham_line(&begin, &end);
		draw_line(display);
		tmp_angle -= 0.1;
	}
}


t_line	*bresenham_line(t_point *begin, t_point *end)
{
	int delta_x;
	int delta_y;
	int x_step;
	int y_step;
	int err;
	int dp;
	t_point current;
	t_line *head;
	t_line *new_node;
	
	head = NULL;
	delta_x = ft_abs(end->x - begin->x);
	delta_y = ft_abs(end->y - begin->y);
	if ((begin->x < end->x))
		x_step = 1;
	else
		x_step = -1;
	if ((begin->y < end->y))
		y_step = 1;
	else
		y_step = -1;
	err = delta_x - delta_y;
	current = *begin;
	while (1)
	{
		new_node = ft_linenew(current);
		ft_lineadd_back(&head, new_node);
		if (head == NULL)
			head = new_node;
		if (current.x == end->x && current.y == end->y)
			break ;
		dp = 2 * err;
		if (dp > -delta_y)
		{
			err -= delta_y;
			current.x += x_step;
		}
		if (dp < delta_x)
		{
			err += delta_x;
			current.y += y_step;
		}
		//mlx_pixel_put();
	}
	return (head);
}