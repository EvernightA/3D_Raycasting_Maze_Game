/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/20 10:36:45 by fsamy-an         ###   ########.fr       */
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
			if (hit.wall_direction == NORTH || hit.wall_direction == SOUTH)
				uv_x = (float)(hit.collision.x % 16) / 16;
			else
				uv_x = (float)(hit.collision.y % 16) / 16;
            uv_y = (float)(count * 16) / line_size / 16;
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

t_hit		draw_line_2(t_display *display, float beta)
{
	t_line *tmp;
	t_point tmp_bloc;
	t_hit 	hit;

	tmp = display->head;
	hit.distance = 0;
	hit.collision.x = 0;
	hit.collision.y = 0;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0' || is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
		{
			img_pix_put(&display->rays, tmp->dot.x, tmp->dot.y, 0x00F0);
		}
		else
		{
			hit.collision = tmp->dot;
			hit.distance = to_wall(display, tmp->dot, beta);
			hit.wall_direction = get_wall_direction(hit.collision, display->player.blocs);
			break;
		}
		tmp = tmp -> next;
	}
	// ft_printf(" = %d\n", distance);
	return (hit);
}