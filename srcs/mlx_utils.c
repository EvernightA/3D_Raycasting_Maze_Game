/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/08 17:44:08 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub.h"

int	quit_win(t_display *display)
{
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.floor_img);
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.wall_img);
	mlx_destroy_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	mlx_destroy_display(display->mlx.mlx_ptr);
	free(display->mlx.mlx_ptr);
	exit(0);
}

int			to_wall(t_display *display, t_point collision)
{
	/*fishbowl effect not corrected yet*/
	return (abs(display->player.pixels.x - collision.x) / cos(FOV));
}

void	player_move (t_display *display, int operation)
{
	display->player.pixels.x = display->player.pixels.x + display->player.delta_x * operation;
	display->player.pixels.y = display->player.pixels.y + display->player.delta_y * operation;
	display->begin.y = display->player.pixels.y;
	display->begin.x = display->player.pixels.x;
	display->player.blocs = pixel_to_bloc(display->player.pixels, display);
	display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
}


void	orientation_player(t_display * display, int operation)
{
	rotate_player(display, TETA);
	display->player.angle = display->player.angle + TETA * operation;
	if (display->player.angle < 0)
	{
		display->player.angle += 2 * M_PI;
	}
	display->player.delta_x = cos (display->player.angle) * 5;
	display->player.delta_y = sin (display->player.angle) * 5;
	printf("%f\n", display->player.angle);
}


int key_hook(int key, void *param)
{
	t_display *display;
	t_point		tmp;

	display = (t_display *)param;
	mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	mlx_clear_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr);
	display->all.mlx_img = mlx_new_image(display->mlx.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT);
	display->rays.mlx_img = mlx_new_image(display->mlx.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT);
	if (!display->all.mlx_img || !display->rays.mlx_img)
		return (0);
	display->all.addr = mlx_get_data_addr(display->all.mlx_img, &display->all.bpp, &display->all.line_len, &display->all.endian);
	display->rays.addr = mlx_get_data_addr(display->rays.mlx_img, &display->rays.bpp, &display->rays.line_len, &display->rays.endian);
	if (key == XK_Escape)
		quit_win(display);
	else if (key == XK_W || key == XK_w)
	{
		// tmp is too see if next is a wall
			tmp.x = display->player.pixels.x + display->player.delta_x;
			tmp.y = display->player.pixels.y + display->player.delta_y;
			tmp = pixel_to_bloc(tmp, display);
			if (display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
			{
				player_move (display, 1);
			}
	}
	else if (key == XK_S || key == XK_s)
	{
		// tmp is too see if next is a wall
		tmp.x = display->player.pixels.x - display->player.delta_x;
		tmp.y = display->player.pixels.y - display->player.delta_y;
		tmp = pixel_to_bloc(tmp, display);
		if (display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			player_move (display, -1);
		}
	}
	else if (key == XK_A || key == XK_a)
		// tmp is too see if next is a wall
	{
		tmp.x = display->player.pixels.x - 1;
		tmp.y = display->player.pixels.y;
		tmp = pixel_to_bloc(tmp, display);
		if (display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			display->player.pixels.x--;
			display->begin.x = display->player.pixels.x;
			display->player.blocs = pixel_to_bloc(display->player.pixels, display);
			display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
		}
	}
	else if (key == XK_D || key == XK_d)
	{
		// tmp is too see if next is a wall
		tmp.x = display->player.pixels.x + 1;
		tmp.y = display->player.pixels.y;
		tmp = pixel_to_bloc(tmp, display);
		if (display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			display->player.pixels.x++;
			display->begin.x = display->player.pixels.x;
			display->player.blocs = pixel_to_bloc(display->player.pixels, display);
			display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
		}
	}
	else if (key == XK_Left)
	{
		orientation_player(display, -1);
	}
	else if (key == XK_Right)
	{
		orientation_player(display, 1);
	}
	cast_ray(display->begin, display, 1000);
	mlx_put_image_to_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr, display->all.mlx_img, 0, 0);
	mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->rays.mlx_img, 0, 0);
	mlx_destroy_image(display->mlx2.mlx_ptr, display->all.mlx_img);
	// free(display->all.addr);
	// display->all.addr = NULL;
	mini_map(display, display->map);
	return (0);
}
