/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:42:50 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/09 13:21:23 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_player_position(t_display *display)
{
	int	i;
	int	j;

	j = 0;
	while (display->map[j])
	{
		i = 0;
		while (display->map[j][i])
		{
			if (is_player(display->map[j][i]))
			{
				init_player_pos(display, i, j);
				orientation_init(display, i, j);
				display->player.orientation = display->map[j][i];
				calculus_dir(display);
				return ;
			}
			i++;
		}
		j++;
	}
}

t_point	pixel_to_bloc(t_point pixel, t_display *display)
{
	t_point	bloc;

	bloc.x = pixel.x >> display->shifter.size_img;
	bloc.y = pixel.y >> display->shifter.size_img;
	bloc.f_x = pixel.x >> display->shifter.size_img;
	bloc.f_y = pixel.y >> display->shifter.size_img;
	return (bloc);
}

void	mlx_functions(t_display *display)
{
	render_all(display);
	mlx_hook(display->mlx2.win_ptr, 17, 0, quit_win, display);
	mlx_hook(display->mlx2.win_ptr, 2, 1L << 0, key_hook, display);
	mlx_hook(display->mlx2.win_ptr, 3, 1L << 1, releasing_key, display);
	mlx_loop_hook(display->mlx2.mlx_ptr, &game_engine, display);
}

int	main(int argc, char **argv)
{
	int			map_height;
	t_display	display;

	(void)argv;
	init_it(&display);
	if (something_is_wrong(&display, argv, argc, &map_height))
	{
		free_tex_map(&display);
		return (1);
	}
	init_player_position(&display);
	display.mlx2.mlx_ptr = mlx_init();
	if (!display.mlx2.mlx_ptr)
		return (1);
	mlx_do_key_autorepeatoff(display.mlx2.mlx_ptr);
	display.mlx2.win_ptr = mlx_new_window(display.mlx2.mlx_ptr, SCRN_WIDTH,
			SCRN_HEIGHT, "cub3D");
	img_initialization(&display);
	load_textures(&display);
	mlx_functions(&display);
	mlx_loop(display.mlx2.mlx_ptr);
	mlx_do_key_autorepeaton(display.mlx2.mlx_ptr);
	free_texture(&display);
	return (0);
}
