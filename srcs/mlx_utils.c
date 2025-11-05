/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/05 11:16:05 by fsamy-an         ###   ########.fr       */
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

int key_hook(int key, void *param)
{
	t_display *display;
	t_point		tmp;

	display = (t_display *)param;
	mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	mlx_clear_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr);
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
				display->player.pixels.x += display->player.delta_x;
				display->player.pixels.y += display->player.delta_y;
				display->begin.y = display->player.pixels.y;
				display->begin.x = display->player.pixels.x;
				display->player.blocs = pixel_to_bloc(display->player.pixels, display);
				display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
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
			display->player.pixels.x -= display->player.delta_x;
			display->player.pixels.y -= display->player.delta_y;
			display->begin.y = display->player.pixels.y;
			display->begin.x = display->player.pixels.x;
			display->player.blocs = pixel_to_bloc(display->player.pixels, display);
			display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
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
		rotate_player(display, TETA);
		display->player.angle -= TETA;
		if (display->player.angle < 0)
		{
			display->player.angle += 2 * M_PI;
		}
		display->player.delta_x = cos (display->player.angle) * 5;
		display->player.delta_y = sin (display->player.angle) * 5;
		printf("%f\n", display->player.angle);
	}
	else if (key == XK_Right)
	{
		rotate_player(display, TETA);
		display->player.angle += TETA;
		if (display->player.angle > 2 * M_PI)
		{
			display->player.angle -= 2 * M_PI;
		}
		display->player.delta_x = cos (display->player.angle) * 5;
		display->player.delta_y = sin (display->player.angle) * 5;
		printf("%f\n", display->player.angle);
	}
	cast_ray(display->begin, display, 1000);
	//ray_fov(display->begin, display, 1000);
	mini_map(display, display->map);
	return (0);
}
