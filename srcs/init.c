/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:27:43 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/09 13:28:14 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_initialization(t_display *display)
{
	int	x;
	int	y;

	display->texture.wall_img = mlx_xpm_file_to_image(display->mlx2.mlx_ptr,
			"./textures/f.xpm", &x, &y);
	display->texture.floor_img = mlx_xpm_file_to_image(display->mlx2.mlx_ptr,
			"./textures/w.xpm", &x, &y);
	display->all.mlx_img = mlx_new_image(display->mlx2.mlx_ptr, SCRN_WIDTH,
			SCRN_HEIGHT);
	if (!display->all.mlx_img)
		return ;
	display->all.addr = mlx_get_data_addr(display->all.mlx_img,
			&display->all.bpp, &display->all.line_len, &display->all.endian);
}

void	init_player_pos(t_display *display, int i, int j)
{
	display->player.blocs.x = i;
	display->player.blocs.y = j;
	display->begin.x = i * 16 + (16 >> 1);
	display->begin.y = j * 16 + (16 >> 1);
	display->begin.f_x = i * 16 + (16 >> 1);
	display->begin.f_y = j * 16 + (16 >> 1);
	display->player.pixels.x = i * 16 + (16 >> 1);
	display->player.pixels.y = j * 16 + (16 >> 1);
	display->player.pixels.f_x = i * 16 + (16 >> 1);
	display->player.pixels.f_y = j * 16 + (16 >> 1);
	display->player.fov = 60;
}

void	init_direction(t_display *display, int x_dir, int y_dir, float angle)
{
	display->player.direction.x = x_dir;
	display->player.direction.y = y_dir;
	display->player.angle = angle;
}

void	init_it(t_display *display)
{
	display->texture.north = NULL;
	display->texture.south = NULL;
	display->texture.east = NULL;
	display->texture.west = NULL;
	display->texture.f_rgb = NULL;
	display->texture.c_rgb = NULL;
	display->map = NULL;
	display->head = NULL;
	display->texture.dup_map = NULL;
	display->key_stat.a_press = false;
	display->key_stat.d_press = false;
	display->key_stat.left_press = false;
	display->key_stat.right_press = false;
	display->key_stat.w_press = false;
	display->key_stat.s_press = false;
	display->shifter.screen_width = shifter(SCRN_WIDTH);
	display->shifter.sreen_height = shifter(SCRN_HEIGHT);
	display->shifter.size_img = shifter(SIZE_IMG);
	display->end.x = 0;
	display->end.y = 0;
}

void	orientation_init(t_display *display, int i, int j)
{
	if (display->map[j][i] == 'N')
		init_direction(display, 0, 1, 3 * M_PI / 2);
	else if (display->map[j][i] == 'S')
		init_direction(display, 0, 1, M_PI / 2);
	else if (display->map[j][i] == 'E')
		init_direction(display, 1, 0, 0);
	else if (display->map[j][i] == 'W')
		init_direction(display, -1, 0, M_PI);
}
