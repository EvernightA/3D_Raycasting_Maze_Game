/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/10/20 12:48:38 by mratsima         ###   ########.fr       */
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

int key_hook(int key, void *param)
{
	t_display *display;

	display = (t_display *)param;
	if (key == XK_Escape)
		quit_win(display);
	else if (key == XK_Up)
	{
		if (display->map[display->player.y_blocs - 1][display->player.x_blocs] == '0')
		{
			display->player.y_pixel--;
			display->player.y_blocs = display->player.y_pixel / 16;
			if (is_player(display->map[display->player.y_blocs + 1][display->player.x_blocs]))
				display->map[display->player.y_blocs + 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
		else if (display->map[display->player.y_blocs - 1][display->player.x_blocs] == '1'
			&& (display->player.y_pixel - 1) % 16)
		{
			display->player.y_pixel--;
			display->player.y_blocs = display->player.y_pixel / 16;
			if (is_player(display->map[display->player.y_blocs + 1][display->player.x_blocs]))
				display->map[display->player.y_blocs + 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
	}
	else if (key == XK_Down)
	{
		if (display->map[display->player.y_blocs + 1][display->player.x_blocs] == '0')
		{
			display->player.y_pixel++;
			display->player.y_blocs = display->player.y_pixel / 16;
			if (is_player(display->map[display->player.y_blocs - 1][display->player.x_blocs]))
				display->map[display->player.y_blocs - 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
		else if (display->map[display->player.y_blocs + 1][display->player.x_blocs] == '1'
			&& (display->player.y_pixel + 1) % 16)
		{
			display->player.y_pixel++;
			display->player.y_blocs = display->player.y_pixel / 16;
			if (is_player(display->map[display->player.y_blocs - 1][display->player.x_blocs]))
				display->map[display->player.y_blocs - 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
	}
	else if (key == XK_Left)
	{
		if (display->map[display->player.y_blocs][display->player.x_blocs - 1] == '0')
		{	
			display->player.x_pixel--;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs + 1]))
				display->map[display->player.y_blocs][display->player.x_blocs + 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
		else if (display->map[display->player.y_blocs][display->player.x_blocs - 1] == '1'
			&& (display->player.x_pixel - 1) % 16)
		{
			display->player.x_pixel--;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs + 1]))
				display->map[display->player.y_blocs][display->player.x_blocs + 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
	}
	else if (key == XK_Right)
	{
		if (display->map[display->player.y_blocs][display->player.x_blocs + 1] == '0')
		{
			display->player.x_pixel++;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs - 1]))
				display->map[display->player.y_blocs][display->player.x_blocs - 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
		else if (display->map[display->player.y_blocs][display->player.x_blocs + 1] == '1'
			&& (display->player.x_pixel + 1) % 16)
		{
			display->player.x_pixel++;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs - 1]))
				display->map[display->player.y_blocs][display->player.x_blocs - 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			print_map(display->map);
			puts("~\n~");
		}
	}
	mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	mini_map(display, display->map);
	return (0);
}