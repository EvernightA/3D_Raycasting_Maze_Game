/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/21 16:30:15 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub.h"

void	rad_to_deg(double rad)
{
	printf("angle en deg = %f\n", 180 * rad / M_PI);
	// printf("cos = %f, sin = %f\n", cos(rad), sin(rad));

}

int	quit_win(t_display *display)
{
	mlx_do_key_autorepeaton(display->mlx.mlx_ptr);/*Cette fonction les reactive faut toujours reactiver a chaque fois*/
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.floor_img);
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.wall_img);
	mlx_destroy_image(display->mlx.mlx_ptr, display->rays.mlx_img);
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.t_east.img_ptr);
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.t_north.img_ptr);
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.t_west.img_ptr);
	mlx_destroy_image(display->mlx.mlx_ptr, display->texture.t_south.img_ptr);

	//mlx_destroy_image(display->mlx2.mlx_ptr, display->all.mlx_img);
	mlx_destroy_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	//mlx_destroy_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr);
	mlx_destroy_display(display->mlx.mlx_ptr);
	//mlx_destroy_display(display->mlx2.mlx_ptr);
	free(display->mlx.mlx_ptr);
	//free(display->mlx2.mlx_ptr);

	free(display->texture.c_rgb);
	free(display->texture.f_rgb);
	free(display->texture.north);
	free(display->texture.south);
	free(display->texture.east);
	free(display->texture.west);
	free_split(display->texture.dup_map);
	free_split(display->map);
	//free(display->all.);
	exit(0);
}

float to_wall(t_display *display, t_point collision, float beta)
{
	float distance;
	int dx;
	int dy;

	dx = display->player.pixels.x - collision.x;
	dy = display->player.pixels.y - collision.y;
	distance = sqrt(pow(abs(dx), 2) + pow(abs(dy), 2));
	distance = distance * cos(beta);
	return (distance);
}


void	player_move (t_display *display, int op, bool is_float)
{
	if (!is_float)
	{
		display->player.pixels.x = display->player.pixels.x + display->player.delta_x * op;
		display->player.pixels.y = display->player.pixels.y + display->player.delta_y * op;
		display->begin.y = display->player.pixels.y;
		display->begin.x = display->player.pixels.x;
		display->player.blocs = pixel_to_bloc(display->player.pixels, display);
		display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
	}
	else
	{
		display->player.pixels.x = display->player.pixels.x  + roundf(display->player.perp_x) * op;
		display->player.pixels.y = display->player.pixels.y  + roundf(display->player.perp_y) * op;
		display->begin.y = display->player.pixels.y;
		display->begin.x = display->player.pixels.x;
		display->player.blocs = pixel_to_bloc(display->player.pixels, display);
		display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
	}
}

void	orientation_player(t_display * display, int operation)
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
	display->player.delta_x = cosf (display->player.angle) * SPEED;
	display->player.delta_y = sinf (display->player.angle) * SPEED;
	display->player.perp_x = -sinf(display->player.angle) *  SPEED;
	display->player.perp_y = cosf(display->player.angle) * SPEED;

	// printf("%f\n", display->player.angle);
}

void	render_all(t_display *display)
{
	aff_floor_and_ceiling(display);
	cast_ray(display->begin, display, MAX_DISTANCE);
	mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->all.mlx_img, 0, 0);
	//mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->rays.mlx_img, 0, 0);
	//mini_map(display, display->map);
}


void	tmp_debug(t_point tmp)
{
	ft_putstr_fd("x = ", 1);
	ft_putnbr_fd(tmp.x, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("y = ", 1);
	ft_putnbr_fd(tmp.y, 1);
	ft_putstr_fd("\n", 1);
}

int key_hook(int key, void *param)
{
	t_display *display;
	// t_point		tmp;

	display = (t_display *)param;
	// mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	// mlx_clear_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr);
	
	if (key == XK_Escape)
		quit_win(display);
	else if (key == XK_W || key == XK_w)
	{
		// tmp is too see if next is a wall
		display->key_stat.w_press = true;
	}
	else if (key == XK_S || key == XK_s)
	{
		// tmp is too see if next is a wall
		display->key_stat.s_press = true;
	}
	else if (key == XK_A || key == XK_a)
	{
		display->key_stat.a_press = true;
	}
	else if (key == XK_D || key == XK_d)
	{
		display->key_stat.d_press = true;
	}
	else if (key == XK_Left)
	{
		display->key_stat.left_press = true;
	}
	else if (key == XK_Right)
	{
		display->key_stat.right_press = true;
	}
	
	return (0);
}
/*
The problem is not the forgottten  frees of bresenham
nor the pixel put
nor the mlx_clear window
*/