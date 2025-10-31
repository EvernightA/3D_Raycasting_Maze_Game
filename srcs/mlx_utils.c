/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/10/31 14:59:16 by fsamy-an         ###   ########.fr       */
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

void	laser(t_display *display)
{
	mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	if (display->head)
		ft_linefree(&display->head);
	display->head = NULL;
	display->head = bresenham_line(&display->begin, &display->end);
	draw_line(display);
}


int key_hook(int key, void *param)
{
	t_display *display;

	display = (t_display *)param;
	mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);

	if (key == XK_Escape)
		quit_win(display);
	else if (key == XK_W || key == XK_w)
	{
		//add here 
		if (display->map[display->player.y_blocs - 1][display->player.x_blocs] == '0')
		{
			ft_printf("%d\n", display->player.angle);
			display->player.x_pixel = display->player.x_pixel + cos(display->player.angle);
			display->player.y_pixel = display->player.y_pixel + sin(display->player.angle);
			display->begin.y = display->player.y_pixel;
			display->begin.x = display->player.x_pixel;
			display->player.y_blocs = display->player.y_pixel / 16;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs + 1][display->player.x_blocs]))
				display->map[display->player.y_blocs + 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;
;
		}
		else if (display->map[display->player.y_blocs - 1][display->player.x_blocs] == '1'
			&& (display->player.y_pixel - 1) % 16)
		{
			display->player.x_pixel = display->player.x_pixel + cos(display->player.angle);
			display->player.y_pixel = display->player.y_pixel + sin(display->player.angle);
			display->begin.y = display->player.y_pixel;
			display->begin.x = display->player.x_pixel;
			display->player.y_blocs = display->player.y_pixel / 16;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs + 1][display->player.x_blocs]))
				display->map[display->player.y_blocs + 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;
		}
	}
	else if (key == XK_S || key == XK_s)
	{
		// add here
		if (display->map[display->player.y_blocs + 1][display->player.x_blocs] == '0')
		{
			display->player.y_pixel++;
			display->begin.y = display->player.y_pixel;
			

			display->player.y_blocs = display->player.y_pixel / 16;
			if (is_player(display->map[display->player.y_blocs - 1][display->player.x_blocs]))
				display->map[display->player.y_blocs - 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			//printf ("head = %p\n", )
			
			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;


		}
		else if (display->map[display->player.y_blocs + 1][display->player.x_blocs] == '1'
			&& (display->player.y_pixel + 1) % 16)
		{
			display->player.y_pixel++;
			display->begin.y = display->player.y_pixel;
			
			
			display->player.y_blocs = display->player.y_pixel / 16;
			if (is_player(display->map[display->player.y_blocs - 1][display->player.x_blocs]))
				display->map[display->player.y_blocs - 1][display->player.x_blocs] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			
			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;


		}
	}
	else if (key == XK_A || key == XK_a)
	{
		if (display->map[display->player.y_blocs][display->player.x_blocs - 1] == '0')
		{	
			display->player.x_pixel--;
			display->begin.x = display->player.x_pixel;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs + 1]))
				display->map[display->player.y_blocs][display->player.x_blocs + 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			display->end.y = display->player.y_pixel + 24;
			display->end.x = display->player.x_pixel + 24;
		}
		else if (display->map[display->player.y_blocs][display->player.x_blocs - 1] == '1'
			&& (display->player.x_pixel - 1) % 16)
		{
			display->player.x_pixel--;
			display->begin.x = display->player.x_pixel;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs + 1]))
				display->map[display->player.y_blocs][display->player.x_blocs + 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			
			
			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;

			

		}
	}
	else if (key == XK_D || key == XK_d)
	{
		if (display->map[display->player.y_blocs][display->player.x_blocs + 1] == '0')
		{
			display->player.x_pixel++;
			display->begin.x = display->player.x_pixel;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs - 1]))
				display->map[display->player.y_blocs][display->player.x_blocs - 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;

			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;
		}
		else if (display->map[display->player.y_blocs][display->player.x_blocs + 1] == '1'
			&& (display->player.x_pixel + 1) % 16)
		{
			display->player.x_pixel++;
			display->begin.x = display->player.x_pixel;
			display->player.x_blocs = display->player.x_pixel / 16;
			if (is_player(display->map[display->player.y_blocs][display->player.x_blocs - 1]))
				display->map[display->player.y_blocs][display->player.x_blocs - 1] = '0';
			display->map[display->player.y_blocs][display->player.x_blocs] = display->player.orientation;
			// display->end.x = display->player.x_pixel + 24;
			// display->end.y = display->player.y_pixel + 24;	
		}
	}
	else if (key == XK_Left)
	{
		rotate_player(display, TETA);
		laser(display);
		ft_printf("before %d\n", display->player.angle);
		display->player.angle += TETA;
		ft_printf("after %d\n", display->player.angle);
	}
	else if (key == XK_Right)
	{
		rotate_player(display, -TETA);
		ft_printf("before %d\n", display->player.angle);
		display->player.angle -= TETA;
		ft_printf("after %d\n", display->player.angle);
	}

	mini_map(display, display->map);
	return (0);
}
