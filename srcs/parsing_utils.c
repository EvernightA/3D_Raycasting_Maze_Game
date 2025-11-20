/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:27:44 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/20 10:30:49 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

int	parsing(int *map_height, char *file, t_display *display)
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
		free_tex_map(display);
		return (1);
	}
	filter_texture(display);
	return (0);
}
