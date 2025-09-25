/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:22:35 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 11:50:46 by mratsima         ###   ########.fr       */
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
		texture->completed++;
	}
	else if (ft_strncmp("SO ", tmp, 3) == 0 || ft_strncmp("SO\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->south = ft_strdup(file);
		texture->completed++;
	}
	else if (ft_strncmp("WE ", tmp, 3) == 0 || ft_strncmp("WE\t", tmp, 3) == 0) 
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->west = ft_strdup(file);
		texture->completed++;
	}
	else if (ft_strncmp("EA ", tmp, 3) == 0 || ft_strncmp("EA\t", tmp, 3) == 0)
	{
		file = ft_strnstr(str,".", ft_strlen(str));
		texture->east = ft_strdup(file);
		texture->completed++;
	}
	else if (ft_strncmp("C ", tmp, 2) == 0 || ft_strncmp("C\t", tmp, 2) == 0)
	{
		texture->c_rgb = ft_strdup(tmp);
		texture->completed++;
	}
	else if (ft_strncmp("F ", tmp, 2) == 0 || ft_strncmp("F\t", tmp, 2) == 0)
	{
		texture->f_rgb = ft_strdup(tmp);
		texture->completed++;
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
	text->completed = 0;
	text->north = NULL;
	text->south = NULL;
	text->east = NULL;
	text->west =  NULL;
	text->f_rgb = NULL;
	text->c_rgb = NULL;
}

int	main(int argc, char **argv)
{
	(void)argv;
	int fd;
	int map_height;
	t_tex	texture;
	t_point begin;
	t_point end;
	t_line *head;
	t_mlx	mlx;

	init_it(&texture);
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <path to the map>\n",2);
		return (0);
	}
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (0);
	}
	map_height = count_map_lines(fd);
	close(fd);
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (0);
	}
	get_elements(fd, &texture, map_height);
	filter_texture(&texture);
	if (texture.completed != 6)
	{
		ft_putstr_fd("Error\nMissing or Invalid identifier\n", 2);
		return (0);
	}
	// see_it(&texture);
	
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
	print_list(head);	
	/*********MLX******************/
	mlx_hook(mlx.win_ptr, 17, 0, quit_win, &mlx);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	/******************************/
	free_texture(&texture);
	return (0);
}