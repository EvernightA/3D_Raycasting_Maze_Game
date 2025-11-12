/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/12 10:36:05 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub.h"

void	rad_to_deg(double rad)
{
	printf("angle en deg = %f\n", 180 * rad / M_PI);
}

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
	(void)display;
	(void)collision;
	// return ();

	return (abs(display->player.pixels.x - collision.x) * tan(FOV));
}

void	player_move (t_display *display, int opx, int opy, double angle)
{
	display->player.pixels.x = display->player.pixels.x + cos(angle) * opx;
	display->player.pixels.y = display->player.pixels.y + sin(angle) * opy;
	display->begin.y = display->player.pixels.y;
	display->begin.x = display->player.pixels.x;
	display->player.blocs = pixel_to_bloc(display->player.pixels, display);
	display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
}


void	orientation_player(t_display * display, int operation)
{
	rotate_player(display, TETA * operation);
	display->player.angle = display->player.angle + TETA * operation;
	display->player.rl_angle = display->player.rl_angle + TETA * operation;
	if (display->player.angle < 0)
	{
		display->player.angle += 2 * M_PI;
	}
	if (display->player.rl_angle < 0)
	{
		display->player.angle += 2 * M_PI;
	}
	display->player.delta_x = cos (display->player.angle) * 5;
	display->player.delta_y = sin (display->player.angle) * 5;
	// printf("%f\n", display->player.angle);
}

void	render_all(t_display *display)
{
	cast_ray(display->begin, display, 500);
	mlx_put_image_to_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr, display->all.mlx_img, 0, 0);
	mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->rays.mlx_img, 0, 0);
	mini_map(display, display->map);
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
	t_point		tmp;

	display = (t_display *)param;
	// mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	// mlx_clear_window(display->mlx2.mlx_ptr, display->mlx2.win_ptr);
	clear_img(display);
	clear_rays(display);
	if (key == XK_Escape)
		quit_win(display);
	else if (key == XK_W || key == XK_w)
	{
		// tmp is too see if next is a wall
			tmp.x = display->player.pixels.x + display->player.delta_x;
			tmp.y = display->player.pixels.y + display->player.delta_y;
			tmp = pixel_to_bloc(tmp, display);

			if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
			{
				player_move (display, 1, 1, display->player.angle);
			}
		render_all(display);
	}
	else if (key == XK_S || key == XK_s)
	{
		// tmp is too see if next is a wall
		tmp.x = display->player.pixels.x - display->player.delta_x;
		tmp.y = display->player.pixels.y - display->player.delta_y;
		tmp = pixel_to_bloc(tmp, display);
		if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			player_move (display, -1, -1, display->player.angle);
		}
		// clear_img(display->all.mlx_img);
		// clear_img(display->rays.mlx_img);
		render_all(display);
		
	}
	else if (key == XK_A || key == XK_a)
		// tmp is too see if next is a wall
	{
		tmp.x = display->player.pixels.x + cos(display->player.rl_angle) * 5;
		tmp.y = display->player.pixels.y + sin(display->player.rl_angle) * 5;
		tmp = pixel_to_bloc(tmp, display);
		if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			player_move(display, 1, 1, display->player.rl_angle);
		}
		render_all(display);

	}
	else if (key == XK_D || key == XK_d)
	{
		// tmp is too see if next is a wall
		tmp.x = display->player.pixels.x - cos(display->player.rl_angle) * 5;
		tmp.y = display->player.pixels.y - sin(display->player.rl_angle) * 5;
		tmp = pixel_to_bloc(tmp, display);
		if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			player_move(display, -1, -1, display->player.rl_angle);
		}
		render_all(display);

	}
	else if (key == XK_Left)
	{
		orientation_player(display, 1);
		rad_to_deg(display->player.angle);
		rad_to_deg(display->player.rl_angle);
		render_all(display);
	}
	else if (key == XK_Right)
	{
		orientation_player(display, -1);
		rad_to_deg(display->player.angle);
		rad_to_deg(display->player.angle);
		render_all(display);
	}
	
	return (0);
}
/*
The problem is not the forgottten  frees of bresenham
nor the pixel put
nor the mlx_clear window
*/