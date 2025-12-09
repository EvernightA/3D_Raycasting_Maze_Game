/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:38:28 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/09 19:34:32 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_texture(t_img_texture **texture_to_display, t_hit hit,
		t_display *display)
{
	(void)texture_to_display;
	if (hit.wall_direction == NORTH)
		*texture_to_display = &display->texture.t_north;
	else if (hit.wall_direction == SOUTH)
		*texture_to_display = &display->texture.t_south;
	else if (hit.wall_direction == EAST)
		*texture_to_display = &display->texture.t_east;
	else
		*texture_to_display = &display->texture.t_west;
}

void	draw_textured_line(t_line *line, t_hit hit, int line_size,
		t_display *display)
{
	t_tex_utils	utils;
	float		uv_x;
	float		uv_y;
	int			texture_color;

	utils.tmp = line;
	utils.count = 0;
	utils.texture_to_display = &display->texture.t_north;
	set_texture(&utils.texture_to_display, hit, display);
	while (utils.tmp)
	{
		if (hit.wall_direction == NORTH || hit.wall_direction == SOUTH)
			uv_x = fmodf(hit.collision.f_x, SIZE_IMG) / SIZE_IMG;
		else
			uv_x = fmodf(hit.collision.f_y, SIZE_IMG) / SIZE_IMG;
		uv_y = (float)utils.count / line_size;
		texture_color = sample_texture(utils.texture_to_display, uv_x, uv_y);
		img_pix_put(&display->all, utils.tmp->dot.x, utils.tmp->dot.y,
			texture_color);
		utils.count++;
		utils.tmp = utils.tmp->next;
	}
}

void	draw_line(t_display *display)
{
	t_line	*tmp;
	t_point	tmp_bloc;

	tmp = display->head;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0'
			|| is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
			mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr,
				tmp->dot.x, tmp->dot.y, 0xFF000);
		else
		{
			break ;
		}
		tmp = tmp->next;
	}
}

void	direct_fix(float normalised_x, t_hit *hit, t_point bloc,
		t_display *display)
{
	char	prev_wall_char;
	char	next_wall_char;
	int		dx;
	int		dy;

	dx = (int)(hit->collision.f_x / 16) - display->player.blocs.x;
	dy = (int)(hit->collision.f_y / 16) - display->player.blocs.y;
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
		east_case(normalised_x, hit, bloc, display);
		west_case(normalised_x, hit, bloc, display);
	}
}

int	direction_fix(t_display *display, t_hit *hit, t_point bloc)
{
	float	normalised_x;

	normalised_x = 0;
	if (hit->wall_direction == NORTH || hit->wall_direction == SOUTH)
	{
		bloc = pixel_to_bloc(hit->collision, display);
		if (bloc.y <= 0 || bloc.y >= display->texture.map_height - 1
			|| !(display->map[bloc.y][bloc.x]))
			return (1);
		direct_fix(normalised_x, hit, bloc, display);
	}
	return (0);
}
