/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/11/21 14:02:16 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub.h"

void print_split(char **split)
{
	int i = 0;
	if (!split)
	{
		printf("(null)\n");
		return ;
	}
	while (split[i])
	{
		printf("%s", split[i]);
		i++;
	}
}
void	init_direction(t_display *display, int x_dir, int y_dir, float angle)
{
	display->player.direction.x = x_dir;
	display->player.direction.y = y_dir;
	display->player.angle = angle;
}
 
void	init_player_pos(t_display *display, int i, int j)
{
	display->player.blocs.x = i;
	display->player.blocs.y = j;
	display->begin.x = i  * 16 + (16 >> 1);
	display->begin.y = j  * 16 + (16 >> 1);
	display->player.pixels.x = i * 16 + (16 >> 1);
	display->player.pixels.y = j * 16 + (16 >> 1);
	display->player.fov = 60;
}

void	see_it(t_display *display)
{
	printf("North : %s\n",display->texture.north);
	printf("East : %s\n", display->texture.east);
	printf("West : %s\n", display->texture.west);
	printf("South : %s\n", display->texture.south);
	printf("c_rgb : %s\n", display->texture.c_rgb);
	printf("f_rgb : %s\n", display->texture.f_rgb);
	printf("map = \n");
	print_split(display->map);
}

void	init_it(t_display *display)
{
	display->texture.north = NULL;
	display->texture.south = NULL;
	display->texture.east = NULL;
	display->texture.west =  NULL;
	display->texture.f_rgb = NULL;
	display->texture.c_rgb = NULL;
	display->map =NULL;
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
}

void	calculus_dir(t_display *display)
{
	display->player.delta_x = cos (display->player.angle) * SPEED;
	display->player.delta_y = sin (display->player.angle) * SPEED;
	display->player.perp_x = -display->player.delta_y;
	display->player.perp_y = display->player.delta_x;
}

static int	input_error(int argc, char **argv)
{
	char *tmp;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <path to the map>\n",2);
		return (1);
	}
	tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (tmp == NULL || ft_strncmp(".cub", tmp, 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid extension for map\n", 2);
		return (1);
	}
	return (0);
}

void	init_player_position(t_display *display)
{
	int i;
	int j;

	j = 0;
	while (display->map[j])
	{
		i = 0;
		while (display->map[j][i])
		{
			if (is_player(display->map[j][i]))
			{
				init_player_pos(display, i, j);
				if (display->map[j][i] == 'N')
					init_direction(display, 0, 1, 3 * M_PI/2);
				else if (display->map[j][i] == 'S')
					init_direction(display, 0, 1, M_PI / 2);
				else  if (display->map[j][i] == 'E')
					init_direction(display, 1, 0, 0);
				else if (display->map[j][i] == 'W')
					init_direction(display, -1, 0, M_PI);
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
	t_point bloc;

	bloc.x = pixel.x >> display->shifter.size_img;// size = 16
	bloc.y = pixel.y >> display->shifter.size_img;// size = 16
	return (bloc);
}







int	main(int argc, char **argv)
{
	(void)argv;
	int map_height;
	t_display	display;

	init_it(&display);

	if (input_error(argc, argv))
		return (1);
	if (get_map_height(&display, &map_height, argv[1]))
		return (1);
	if (parsing(&map_height, argv[1], &display))
		return (1);
	if (error_handling(&display))
		return (1);
	init_player_position(&display);
	/************MLX*********/
	display.mlx.mlx_ptr = mlx_init();
	display.mlx2.mlx_ptr = mlx_init();
	if (!display.mlx.mlx_ptr)
		return (1);
	if (!display.mlx2.mlx_ptr)
		return (1);
	mlx_do_key_autorepeatoff(display.mlx.mlx_ptr);/*Cette fonction annule l'auto repetition des touches*/
	display.mlx.win_ptr = mlx_new_window(display.mlx.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT, "cub3d");
	//display.mlx2.win_ptr = mlx_new_window(display.mlx2.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT, "render");
	/*********************/
	img_initialization(&display);
	load_textures(&display);
	display.end.x = display.player.pixels.x + 24;
	display.end.y = display.player.pixels.y + 24;
	//mlx_pixel_put(display.mlx.mlx_ptr, display.mlx.win_ptr, display.end.x, display.end.y, 0XFF000);
	/*********MLX******************/
	//mlx_key_hook(display.mlx.mlx_ptr, display.mlx.win_ptr, &display);
	render_all(&display);
	mlx_hook(display.mlx.win_ptr, 17, 0, quit_win, &display);
	mlx_hook(display.mlx.win_ptr, 2, 1L<<0, key_hook, &display);
	mlx_hook(display.mlx.win_ptr, 3, 1L<<1, releasing_key, &display);
	//mini_map(&display, display.map);
	mlx_loop_hook(display.mlx.mlx_ptr, &game_engine, &display);
	mlx_loop(display.mlx.mlx_ptr);
	mlx_do_key_autorepeaton(display.mlx.mlx_ptr);/*Cette fonction les reactive*/
	free_texture(&display);
	return (0);
}
