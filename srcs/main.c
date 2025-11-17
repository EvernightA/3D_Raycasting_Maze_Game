/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/11/17 07:33:08 by fsamy-an         ###   ########.fr       */
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

void	store_texture(char *str, t_display *display)
{
	char *tmp;
	char *file;

	tmp = ft_strtrim(str, " \t");
	if (ft_strncmp("NO ", tmp, 3) == 0 || ft_strncmp("NO\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		display->texture.north = ft_strdup(file);
	}
	else if (ft_strncmp("SO ", tmp, 3) == 0 || ft_strncmp("SO\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		display->texture.south = ft_strdup(file);
	}
	else if (ft_strncmp("WE ", tmp, 3) == 0 || ft_strncmp("WE\t", tmp, 3) == 0) 
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		display->texture.west = ft_strdup(file);
	}
	else if (ft_strncmp("EA ", tmp, 3) == 0 || ft_strncmp("EA\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		display->texture.east = ft_strdup(file);
	}
	else if (ft_strncmp("C ", tmp, 2) == 0 || ft_strncmp("C\t", tmp, 2) == 0)
	{
		display->texture.c_rgb = ft_strdup(tmp);
	}
	else if (ft_strncmp("F ", tmp, 2) == 0 || ft_strncmp("F\t", tmp, 2) == 0)
	{
		display->texture.f_rgb = ft_strdup(tmp);
	}
	free(tmp);
}


void	filter_texture(t_display *display)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strtrim(display->texture.north, "\n");
	free(display->texture.north);
	display->texture.north = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(display->texture.south, "\n");
	free(display->texture.south);
	display->texture.south = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(display->texture.west, "\n");
	free(display->texture.west);
	display->texture.west = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(display->texture.east, "\n");
	free(display->texture.east);
	display->texture.east = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(display->texture.c_rgb, "\n");
	free(display->texture.c_rgb);
	display->texture.c_rgb = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(display->texture.f_rgb, "\n");
	free(display->texture.f_rgb);
	display->texture.f_rgb = ft_strdup(tmp);
	free(tmp);
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
	display->map = NULL;
	display->head = NULL;
	display->timer.start_time = get_time();
	display->timer.current_time = 0;
	display->timer.last_time = 0;
	display->timer.delta_time = 0;
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
	// mlx loop hook se declenche parfois automatiquement ce qui declenche le mouvements
	display->player.delta_x = cos (display->player.angle) * 2;
	display->player.delta_y = sin (display->player.angle) * 2;
	display->player.perp_x = -sin(display->player.angle) * 2;
	display->player.perp_y = display->player.delta_x;
}

static int	get_map_height(t_display *display, int *map_height ,char *file)
{
	int fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (1);
	}
	*map_height = count_map_lines(fd);
	display->texture.map_height = *map_height;
	close(fd);
	return (0);
}

static int	parsing(int *map_height, char *file, t_display *display)
{
	int fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (1);
	}
	get_elements(fd, display, *map_height);
	if (!display->texture.c_rgb || !display->texture.f_rgb || !display->texture.north 
	|| !display->texture.south || !display->texture.east || !display->texture.west || !display->map)
	{
		ft_putstr_fd("Error\nMissing or Invalid identifier\n", 2);
		return (1);
	}
	filter_texture(display);
	return (0);
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
				display->player.blocs.x = i;
				display->player.blocs.y = j;
				display->begin.x = i  * 16 + (16 >> 1);
				display->begin.y = j  * 16 + (16 >> 1);
				display->player.pixels.x = i * 16 + (16 >> 1);
				display->player.pixels.y = j * 16 + (16 >> 1);
				display->player.fov = 60;
				if (display->map[j][i] == 'N')
				{
					display->player.direction.x = 0;
					display->player.direction.y = -1;
					display->player.angle = 3 * M_PI/2;
				}
				else if (display->map[j][i] == 'S')
				{
					display->player.direction.x = 0;
					display->player.direction.y = 1;
					display->player.angle =  M_PI/2;
				}
				else  if (display->map[j][i] == 'E')
				{
					display->player.direction.x = 1;
					display->player.direction.y = 0;
					display->player.angle = 0;
				}
				else if (display->map[j][i] == 'W')
				{
					display->player.direction.x = -1;
					display->player.direction.y = 0;
					display->player.angle = M_PI;
				}
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
float		draw_line_2(t_display *display, float beta)
{
	t_line *tmp;
	t_point tmp_bloc;
	float	distance;

	tmp = display->head;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0' || is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
		{
			img_pix_put(&display->rays, tmp->dot.x, tmp->dot.y, 0x00F0);
		}
		else
		{
			distance = to_wall(display, tmp->dot, beta);
			break;
		}
		tmp = tmp -> next;
	}
	// ft_printf(" = %d\n", distance);
	return (distance);
}

void		draw_line(t_display *display)
{
	t_line *tmp;
	t_point tmp_bloc;

	tmp = display->head;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0' || is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
			mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr,tmp->dot.x,tmp->dot.y, 0xFF000);
		else
		{
			//printf("fount this here : (%c)\n", display->map[tmp_bloc.y][tmp_bloc.x]);
			break;
		}
		tmp = tmp -> next;
	}
}

void		draw_simple_line2(t_line *line, t_display *display)
{
	t_line *tmp;

	tmp = line;
	while (tmp)
	{
		img_pix_put(&display->all, tmp->dot.x, tmp->dot.y, 0x0000FF);
		tmp = tmp -> next;
	}
}


int	main(int argc, char **argv)
{
	(void)argv;
	int map_height;
	t_display	display;
	//t_point begin;
	//t_point end;
	//t_line *head;

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
	printf("next -one %f\n", display.player.angle);
	/************MLX*********/
	display.mlx.mlx_ptr = mlx_init();
	display.mlx2.mlx_ptr = mlx_init();
	if (!display.mlx.mlx_ptr)
		return (1);
	if (!display.mlx2.mlx_ptr)
		return (1);
	mlx_do_key_autorepeatoff(display.mlx.mlx_ptr);/*Cette fonction annule l'auto repetition des touches*/
	display.mlx.win_ptr = mlx_new_window(display.mlx.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT, "cub3d");
	display.mlx2.win_ptr = mlx_new_window(display.mlx2.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT, "render");
	/*********************/
	img_initialization(&display);
	display.end.x = display.player.pixels.x + 24;
	display.end.y = display.player.pixels.y + 24;
	//mlx_pixel_put(display.mlx.mlx_ptr, display.mlx.win_ptr, display.end.x, display.end.y, 0XFF000);
	/*********MLX******************/
	//mlx_key_hook(display.mlx.mlx_ptr, display.mlx.win_ptr, &display);
	mlx_hook(display.mlx.win_ptr, 17, 0, quit_win, &display);
	mlx_hook(display.mlx.win_ptr, 2, 1L<<0, key_hook, &display);
	mlx_hook(display.mlx.win_ptr, 3, 1L<<1, releasing_key, &display);
	mini_map(&display, display.map);
	mlx_loop_hook(display.mlx.mlx_ptr, &game_engine, &display);
	mlx_loop(display.mlx.mlx_ptr);
	mlx_do_key_autorepeaton(display.mlx.mlx_ptr);/*Cette fonction les reactive*/
	
	/*
	*/

	// mlx_loop(display.mlx2.mlx_ptr); boucle morte
	/******************************/
	free_texture(&display);
	return (0);
}
