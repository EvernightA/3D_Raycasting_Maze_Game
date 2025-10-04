/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:22:35 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/04 14:32:08 by fsamy-an         ###   ########.fr       */
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
	print_split(display->texture.map);
}

void	init_it(t_display *display)
{
	display->texture.north = NULL;
	display->texture.south = NULL;
	display->texture.east = NULL;
	display->texture.west =  NULL;
	display->texture.f_rgb = NULL;
	display->texture.c_rgb = NULL;
	display->texture.map =NULL;
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
	|| !display->texture.south || !display->texture.east || !display->texture.west || !display->texture.map)
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

int	main(int argc, char **argv)
{
	(void)argv;
	int map_height;
	t_display	display;
	t_point begin;
	t_point end;
	t_line *head;

	init_it(&display);
	if (input_error(argc, argv))
		return (1);
	if (get_map_height(&display, &map_height, argv[1]))
		return (1);
	if (parsing(&map_height, argv[1], &display))
		return (1);
	if (error_handling(&display))
		return (1);
	/************MLX*********/
	display.mlx.mlx_ptr = mlx_init();
	if (!display.mlx.mlx_ptr)
		return (1);
	display.mlx.win_ptr = mlx_new_window(display.mlx.mlx_ptr, 400, 400, "cub3d");
	/*********************/
	begin.x = 10;
	begin.y = 0;
	end.x = 30;
	end.y = 40;
	img_initialization(&display);
	head = bresenham_line(&begin, &end);
	(void)head;
	// print_list(head);	
	/*********MLX******************/
	mlx_hook(display.mlx.win_ptr, 17, 0, quit_win, &display);
	mlx_key_hook(display.mlx.win_ptr, key_hook, &display);
	mlx_loop(display.mlx.mlx_ptr);
	/******************************/
	free_texture(&display);
	return (0);
}
