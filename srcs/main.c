/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:22:35 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/02 22:29:38 by fsamy-an         ###   ########.fr       */
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

void	store_texture(char *str, t_tex *texture)
{
	char *tmp;
	char *file;

	tmp = ft_strtrim(str, " \t");
	if (ft_strncmp("NO ", tmp, 3) == 0 || ft_strncmp("NO\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->north = ft_strdup(file);
	}
	else if (ft_strncmp("SO ", tmp, 3) == 0 || ft_strncmp("SO\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->south = ft_strdup(file);
	}
	else if (ft_strncmp("WE ", tmp, 3) == 0 || ft_strncmp("WE\t", tmp, 3) == 0) 
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->west = ft_strdup(file);
	}
	else if (ft_strncmp("EA ", tmp, 3) == 0 || ft_strncmp("EA\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->east = ft_strdup(file);
	}
	else if (ft_strncmp("C ", tmp, 2) == 0 || ft_strncmp("C\t", tmp, 2) == 0)
	{
		texture->c_rgb = ft_strdup(tmp);
	}
	else if (ft_strncmp("F ", tmp, 2) == 0 || ft_strncmp("F\t", tmp, 2) == 0)
	{
		texture->f_rgb = ft_strdup(tmp);
	}
	free(tmp);
}


void	filter_texture(t_tex *texture)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strtrim(texture->north, "\n");
	free(texture->north);
	texture->north = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(texture->south, "\n");
	free(texture->south);
	texture->south = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(texture->west, "\n");
	free(texture->west);
	texture->west = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(texture->east, "\n");
	free(texture->east);
	texture->east = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(texture->c_rgb, "\n");
	free(texture->c_rgb);
	texture->c_rgb = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strtrim(texture->f_rgb, "\n");
	free(texture->f_rgb);
	texture->f_rgb = ft_strdup(tmp);
	free(tmp);
}


void	see_it(t_tex *texture)
{
	printf("North : %s\n",texture->north);
	printf("East : %s\n", texture->east);
	printf("West : %s\n", texture->west);
	printf("South : %s\n", texture->south);
	printf("c_rgb : %s\n", texture->c_rgb);
	printf("f_rgb : %s\n", texture->f_rgb);
	printf("map = \n");
	print_split(texture->map);
}

void	init_it(t_tex *text)
{
	text->north = NULL;
	text->south = NULL;
	text->east = NULL;
	text->west =  NULL;
	text->f_rgb = NULL;
	text->c_rgb = NULL;
	text->map =NULL;
}

static int	get_map_height(t_tex *texture, int *map_height ,char *file)
{
	int fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (1);
	}
	*map_height = count_map_lines(fd);
	texture->map_height = *map_height;
	close(fd);
	return (0);
}

static int	parsing(int *map_height, char *file, t_tex *texture)
{
	int fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (1);
	}
	get_elements(fd, texture, *map_height);
	if (!texture->c_rgb || !texture->f_rgb || !texture->north 
	|| !texture->south || !texture->east || !texture->west || !texture->map)
	{
		ft_putstr_fd("Error\nMissing or Invalid identifier\n", 2);
		return (1);
	}
	filter_texture(texture);
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
	t_tex	texture;
	t_point begin;
	t_point end;
	t_line *head;
	t_mlx	mlx;

	init_it(&texture);
	if (input_error(argc, argv))
		return (1);
	if (get_map_height(&texture, &map_height, argv[1]))
		return (1);
	if (parsing(&map_height, argv[1], &texture))
		return (1);
	if (error_handling(&texture))
		return (1);
	/************MLX*********/
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 400, 400, "cub3d");
	/*********************/
	begin.x = 10;
	begin.y = 0;
	end.x = 30;
	end.y = 40;
	head = bresenham_line(&begin, &end);
	(void)head;
	// print_list(head);	
	/*********MLX******************/
	mlx_hook(mlx.win_ptr, 17, 0, quit_win, &mlx);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	/******************************/
	free_texture(&texture);
	return (0);
}
