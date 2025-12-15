/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:27:44 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/15 15:28:32 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	get_brute_texture(char *str, char **texture, t_display *display)
{
	char	*file;
	char	*new_file;

	file = ft_strnstr(str, ".", ft_strlen(str));
	new_file = ft_strtrim(file, " \t\n");
	if (texture && *texture)
		free(*texture);
	*texture = ft_strdup(new_file);
	display->element_count++;
	free(new_file);
	return ;
}

void	store_texture(char *str, t_display *display)
{
	char	*tmp;

	tmp = ft_strtrim(str, " \t");
	if (ft_strncmp("NO ", tmp, 3) == 0 || ft_strncmp("NO\t", tmp, 3) == 0)
		get_brute_texture(str, &display->texture.north, display);
	else if (ft_strncmp("SO ", tmp, 3) == 0 || ft_strncmp("SO\t", tmp, 3) == 0)
		get_brute_texture(str, &display->texture.south, display);
	else if (ft_strncmp("WE ", tmp, 3) == 0 || ft_strncmp("WE\t", tmp, 3) == 0)
		get_brute_texture(str, &display->texture.west, display);
	else if (ft_strncmp("EA ", tmp, 3) == 0 || ft_strncmp("EA\t", tmp, 3) == 0)
		get_brute_texture(str, &display->texture.east, display);
	else if (ft_strncmp("C ", tmp, 2) == 0 || ft_strncmp("C\t", tmp, 2) == 0)
	{
		if (display->texture.c_rgb)
			free(display->texture.c_rgb);
		display->texture.c_rgb = ft_strdup(tmp);
		display->element_count++;
	}
	else if (ft_strncmp("F ", tmp, 2) == 0 || ft_strncmp("F\t", tmp, 2) == 0)
	{
		if (display->texture.f_rgb)
			free(display->texture.f_rgb);
		display->texture.f_rgb = ft_strdup(tmp);
		display->element_count++;
	}
	free(tmp);
}

void	get_clean_texture(char **texture)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strtrim((*texture), "\n");
	free(*texture);
	(*texture) = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}

void	filter_texture(t_display *display)
{
	get_clean_texture(&display->texture.north);
	get_clean_texture(&display->texture.south);
	get_clean_texture(&display->texture.east);
	get_clean_texture(&display->texture.west);
}

int	get_map_height(t_display *display, int *map_height, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n", 2);
		return (1);
	}
	*map_height = count_map_lines(fd);
	display->texture.map_height = *map_height;
	close(fd);
	return (0);
}
