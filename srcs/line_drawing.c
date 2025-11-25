/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:59 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    draw_textured_line(t_line *line, t_hit hit, int line_size, t_display *display)
{
        t_line *tmp;
		float uv_x;
		float uv_y;
		t_img_texture *texture_to_display;
		int texture_color;
		int count;

        tmp = line;
		count = 0;
		if (hit.wall_direction == NORTH)
			texture_to_display = &display->texture.t_north;
		else if (hit.wall_direction == SOUTH)
			texture_to_display = &display->texture.t_south;
		else if (hit.wall_direction == EAST)
			texture_to_display = &display->texture.t_east;
		else
			texture_to_display = &display->texture.t_west;
        while (tmp)
        {
			// Use precise float coordinates for UV calculation
			if (hit.wall_direction == NORTH || hit.wall_direction == SOUTH)
				uv_x = fmodf(hit.collision.f_x, SIZE_IMG) / SIZE_IMG;
			else
				uv_x = fmodf(hit.collision.f_y, SIZE_IMG) / SIZE_IMG;
            uv_y = (float)count / line_size;
            texture_color = sample_texture(texture_to_display, uv_x, uv_y);
            img_pix_put(&display->all, tmp->dot.x, tmp->dot.y, texture_color);
			count ++;
            tmp = tmp -> next;
        }
}

void		draw_line(t_display *display)
{
	t_line *tmp;
	t_point tmp_bloc;

	tmp = display->head;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0' || is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
			mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr,tmp->dot.x,tmp->dot.y, 0xFF000);
		else
		{
			//printf("fount this here : (%c)\n", display->map[tmp_bloc.y][tmp_bloc.x]);
			break;
		}
		tmp = tmp -> next;
	}
}

int	direction_fix(t_display *display, t_hit *hit, t_point bloc)
{
	float normalised_x;
	char prev_wall_char;
	char next_wall_char;
	int dx;
	int dy;

	dx = (int)(hit->collision.f_x / 16) - display->player.blocs.x;
    dy = (int)(hit->collision.f_y / 16) - display->player.blocs.y;
	if (hit->wall_direction == NORTH || hit->wall_direction == SOUTH)
	{
		bloc = pixel_to_bloc(hit->collision, display);
		if (bloc.y <= 0 || bloc.y >= display->texture.map_height - 1
			|| !(display->map[bloc.y][bloc.x]))
			return (1);
		prev_wall_char = display->map[bloc.y - 1][bloc.x];
		next_wall_char = display->map[bloc.y + 1][bloc.x];
		if (display->map[bloc.y][bloc.x] == prev_wall_char
			&& prev_wall_char == next_wall_char)
		{
			if ((dx < 0 && dy < 0) || (dx < 0 && dy > 0))
				hit->wall_direction = EAST;
			else
				hit->wall_direction = WEST;
		}
		else
		{
			normalised_x = fmodf(hit->collision.f_x, 16);
			if (dx < 0 && dy > 0 && hit->wall_direction == NORTH)
			{
				if (normalised_x >= 14.5f && display->map[bloc.y][bloc.x + 1] != '1')
					hit->wall_direction = EAST;
				if (normalised_x >= 14.5f && display->map[bloc.y + 1][bloc.x] != '1' && display->map[bloc.y - 1][bloc.x] == '1')
					hit->wall_direction = EAST;
			}
			if (dx < 0 && dy < 0 && hit->wall_direction == SOUTH)
			{
				if (normalised_x >= 14.5f && display->map[bloc.y][bloc.x + 1] != '1')
					hit->wall_direction = EAST;
				if (normalised_x >= 14.5f && display->map[bloc.y - 1][bloc.x] != '1' && display->map[bloc.y + 1][bloc.x] == '1')
					hit->wall_direction = EAST;
			}
			if (dx > 0 && dy > 0 && hit->wall_direction == NORTH)
			{
				if (normalised_x <= 0.5f && display->map[bloc.y][bloc.x - 1] != '1')
					hit->wall_direction = WEST;
				if (normalised_x <= 0.5f && display->map[bloc.y + 1][bloc.x] != '1' && display->map[bloc.y - 1][bloc.x] == '1')
					hit->wall_direction = WEST;
			}
			if (dx > 0 && dy < 0 && hit->wall_direction == SOUTH)
			{
				if (normalised_x <= 0.5f && display->map[bloc.y][bloc.x - 1] != '1')
					hit->wall_direction = WEST;
				if (normalised_x <= 0.5f && display->map[bloc.y - 1][bloc.x] != '1' && display->map[bloc.y + 1][bloc.x] == '1')
					hit->wall_direction = WEST;
			}
		}
	}
	return (0);
}

t_hit		draw_line_2(t_display *display, float beta)
{
	t_line *tmp;
	t_line	*before;
	t_point tmp_bloc;
	t_hit 	hit;
	t_point bloc;

	tmp = display->head;
	hit.distance = 0;
	hit.collision.x = 0;
	hit.collision.y = 0;
	hit.collision.f_x = 0;
	hit.collision.f_y = 0;
	before = NULL;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0' || is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
		{
			img_pix_put(&display->rays, tmp->dot.x, tmp->dot.y, 0x00F0);
		}
		else
		{
			// Store the precise float collision coordinates
			hit.collision.x = tmp->dot.x;
			hit.collision.y = tmp->dot.y;
			hit.collision.f_x = tmp->dot.f_x;
			hit.collision.f_y = tmp->dot.f_y;
			hit.distance = to_wall(display, tmp->dot, beta);
			hit.wall_direction = get_wall_direction(hit.collision, display->player.blocs);
			if (direction_fix(display, &hit, bloc))
				break ;
			/****************************fix-for textures and wall direction***************************************************/
			// Use float coordinates for more precise calculations
			// dx = (int)(hit.collision.f_x / 16) - display->player.blocs.x;
    		// dy = (int)(hit.collision.f_y / 16) - display->player.blocs.y;
			// if (hit.wall_direction == NORTH || hit.wall_direction == SOUTH)
			// {
			// 	bloc = pixel_to_bloc(hit.collision, display);
			// 	if (bloc.y <= 0 || bloc.y >= display->texture.map_height - 1
			// 		|| !(display->map[bloc.y][bloc.x]))
			// 		break;
			// 	prev_wall_char = display->map[bloc.y - 1][bloc.x];
			// 	next_wall_char = display->map[bloc.y + 1][bloc.x];
			// 	if (display->map[bloc.y][bloc.x] == prev_wall_char
			// 		&& prev_wall_char == next_wall_char)
			// 	{
			// 		if ((dx < 0 && dy < 0) || (dx < 0 && dy > 0))
			// 			hit.wall_direction = EAST;
			// 		else
			// 			hit.wall_direction = WEST;
			// 	}
			// 	else
			// 	{
			// 		normalised_x = fmodf(hit.collision.f_x, 16);
			// 		if (dx < 0 && dy > 0 && hit.wall_direction == NORTH)
			// 		{
			// 			if (normalised_x >= 14.5f && display->map[bloc.y][bloc.x + 1] != '1')
			// 				hit.wall_direction = EAST;
			// 			if (normalised_x >= 14.5f && display->map[bloc.y + 1][bloc.x] != '1' && display->map[bloc.y - 1][bloc.x] == '1')
			// 				hit.wall_direction = EAST;
			// 		}
			// 		if (dx < 0 && dy < 0 && hit.wall_direction == SOUTH)
			// 		{
			// 			if (normalised_x >= 14.5f && display->map[bloc.y][bloc.x + 1] != '1')
			// 				hit.wall_direction = EAST;
			// 			if (normalised_x >= 14.5f && display->map[bloc.y - 1][bloc.x] != '1' && display->map[bloc.y + 1][bloc.x] == '1')
			// 				hit.wall_direction = EAST;
			// 		}
			// 		if (dx > 0 && dy > 0 && hit.wall_direction == NORTH)
			// 		{
			// 			if (normalised_x <= 0.5f && display->map[bloc.y][bloc.x - 1] != '1')
			// 				hit.wall_direction = WEST;
			// 			if (normalised_x <= 0.5f && display->map[bloc.y + 1][bloc.x] != '1' && display->map[bloc.y - 1][bloc.x] == '1')
			// 				hit.wall_direction = WEST;
			// 		}
			// 		if (dx > 0 && dy < 0 && hit.wall_direction == SOUTH)
			// 		{
			// 			if (normalised_x <= 0.5f && display->map[bloc.y][bloc.x - 1] != '1')
			// 				hit.wall_direction = WEST;
			// 			if (normalised_x <= 0.5f && display->map[bloc.y - 1][bloc.x] != '1' && display->map[bloc.y + 1][bloc.x] == '1')
			// 				hit.wall_direction = WEST;
			// 		}
			// 	}
			// }
			/*************************************************************************************************/
			return (hit);
		}
		if (tmp->next == NULL)
		{
			before = tmp;
			// Store the precise float collision coordinates
			hit.collision.x = before->dot.x;
			hit.collision.y = before->dot.y;
			hit.collision.f_x = before->dot.f_x;
			hit.collision.f_y = before->dot.f_y;
			hit.distance = to_wall(display, before->dot, beta);
			hit.wall_direction = get_wall_direction(hit.collision, display->player.blocs);
			return (hit);

		}
		tmp = tmp -> next;
	}
	
	return (hit);
}