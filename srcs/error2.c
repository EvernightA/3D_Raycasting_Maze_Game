/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:00:37 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/09 14:01:26 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_tex_map(t_display *display)
{
	free(display->texture.c_rgb);
	display->texture.c_rgb = 0;
	free(display->texture.f_rgb);
	display->texture.f_rgb = 0;
	if (display->map)
		free_split(display->map);
	display->map = 0;
	if (display->texture.dup_map)
		free_split(display->texture.dup_map);
	display->texture.dup_map = 0;
	free(display->texture.east);
	display->texture.east = 0;
	free(display->texture.north);
	display->texture.north = 0;
	free(display->texture.south);
	display->texture.south = 0;
	free(display->texture.west);
	display->texture.west = 0;
}

int	closed_error(char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	if (player_in_str(map[0]))
	{
		return (1);
	}
	while (map[j])
	{
		k = 0;
		while (map[j][k])
		{
			if (map_invalid(i, j, k, map))
				return (1);
			k++;
		}
		i++;
		j++;
	}
	if (player_in_str(map[i]) || map[i][0] == '0')
		return (1);
	return (0);
}

int	texture_error(t_display *display)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strnstr(display->texture.north, ".xpm",
			ft_strlen(display->texture.north));
	tmp1 = ft_strnstr(display->texture.south, ".xpm",
			ft_strlen(display->texture.south));
	tmp2 = ft_strnstr(display->texture.west, ".xpm",
			ft_strlen(display->texture.west));
	tmp3 = ft_strnstr(display->texture.east, ".xpm",
			ft_strlen(display->texture.east));
	if (tmp == NULL || tmp1 == NULL || tmp2 == NULL || tmp3 == NULL
		|| ft_strncmp(tmp, ".xpm", 5) != 0 || ft_strncmp(tmp1, ".xpm", 5) != 0
		|| ft_strncmp(tmp2, ".xpm", 5) != 0 || ft_strncmp(tmp3, ".xpm", 5) != 0)
	{
		free_tex_map(display);
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	return (0);
}

int	something_is_wrong(t_display *display, char **argv, int argc,
		int *map_height)
{
	if (input_error(argc, argv))
		return (1);
	if (get_map_height(display, map_height, argv[1]))
		return (1);
	if (parsing(map_height, argv[1], display))
		return (1);
	if (error_handling(display))
		return (1);
	if (get_rgb(&display->texture.floor_rgb, display->texture.f_rgb))
	{
		return (1);
	}
	if (get_rgb(&display->texture.ceiling_rgb, display->texture.c_rgb))
	{
		return (1);
	}
	return (0);
}

int	successive_commas(int *i, char *og_rgb)
{
	while (og_rgb[*i])
	{
		if (og_rgb[*i] == ',' && og_rgb[(*i) + 1] == ',')
		{
			ft_putstr_fd("Error\nWrong rgb value(successive commas)\n", 2);
			return (1);
		}
		(*i)++;
	}
	return (0);
}
