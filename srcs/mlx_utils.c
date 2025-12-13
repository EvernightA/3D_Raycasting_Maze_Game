/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 14:22:17 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	quit_win(t_display *display)
{
	mlx_do_key_autorepeaton(display->mlx2.mlx_ptr);
	if (display->texture.t_east.img_ptr)
		mlx_destroy_image(display->mlx2.mlx_ptr,
			display->texture.t_east.img_ptr);
	if (display->texture.t_north.img_ptr)
		mlx_destroy_image(display->mlx2.mlx_ptr,
			display->texture.t_north.img_ptr);
	if (display->texture.t_north.img_ptr)
		mlx_destroy_image(display->mlx2.mlx_ptr,
			display->texture.t_west.img_ptr);
	if (display->texture.t_north.img_ptr)
		mlx_destroy_image(display->mlx2.mlx_ptr,
			display->texture.t_south.img_ptr);
	mlx_destroy_image(display->mlx2.mlx_ptr, display->all.mlx_img);
	mlx_destroy_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr);
	mlx_destroy_display(display->mlx2.mlx_ptr);
	free(display->mlx2.mlx_ptr);
	free_tex_map(display);
	exit(0);
}

void	player_move(t_display *display, int op, bool is_float)
{
	if (!is_float)
	{
		display->player.pixels.f_x = display->player.pixels.f_x
			+ display->player.delta_x * op;
		display->player.pixels.f_y = display->player.pixels.f_y
			+ display->player.delta_y * op;
	}
	else
	{
		display->player.pixels.f_x = display->player.pixels.f_x
			+ display->player.perp_x * op;
		display->player.pixels.f_y = display->player.pixels.f_y
			+ display->player.perp_y * op;
	}
	display->player.pixels.x = (int)display->player.pixels.f_x;
	display->player.pixels.y = (int)display->player.pixels.f_y;
	display->begin.f_x = display->player.pixels.f_x;
	display->begin.f_y = display->player.pixels.f_y;
	display->begin.x = display->player.pixels.x;
	display->begin.y = display->player.pixels.y;
	display->player.blocs = pixel_to_bloc(display->player.pixels, display);
	display->map[display->player.blocs.y]
	[display->player.blocs.x] = display->player.orientation;
}

void	orientation_player(t_display *display, int operation)
{
	rotate_player(display, TETA * operation);
	display->player.angle = display->player.angle + TETA * operation;
	if (display->player.angle < 0)
	{
		display->player.angle += 2 * M_PI;
	}
	if (display->player.angle >= 2 * M_PI)
	{
		display->player.angle = 0;
	}
	display->player.delta_x = cosf(display->player.angle) * SPEED;
	display->player.delta_y = sinf(display->player.angle) * SPEED;
	display->player.perp_x = -sinf(display->player.angle) * SPEED;
	display->player.perp_y = cosf(display->player.angle) * SPEED;
}

void	render_all(t_display *display)
{
	aff_floor_and_ceiling(display);
	cast_ray(display);
	mlx_put_image_to_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr,
		display->all.mlx_img, 0, 0);
}

int	key_hook(int key, void *param)
{
	t_display	*display;

	display = (t_display *)param;
	if (key == XK_Escape)
		quit_win(display);
	else if (key == XK_W || key == XK_w)
		display->key_stat.w_press = true;
	else if (key == XK_S || key == XK_s)
		display->key_stat.s_press = true;
	else if (key == XK_A || key == XK_a)
		display->key_stat.a_press = true;
	else if (key == XK_D || key == XK_d)
		display->key_stat.d_press = true;
	else if (key == XK_Left)
		display->key_stat.left_press = true;
	else if (key == XK_Right)
		display->key_stat.right_press = true;
	return (0);
}
