/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:00:37 by fsamy-an          #+#    #+#             */
/*   Updated: 2026/02/17 10:14:38 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	t_tmp	t;

	t.tmp = ft_strnstr(display->texture.north, ".xpm",
			ft_strlen(display->texture.north));
	t.tmp1 = ft_strnstr(display->texture.south, ".xpm",
			ft_strlen(display->texture.south));
	t.tmp2 = ft_strnstr(display->texture.west, ".xpm",
			ft_strlen(display->texture.west));
	t.tmp3 = ft_strnstr(display->texture.east, ".xpm",
			ft_strlen(display->texture.east));
	if (t.tmp == NULL || t.tmp1 == NULL || t.tmp2 == NULL || t.tmp3 == NULL
		|| ft_strncmp(t.tmp, ".xpm", 5) != 0
		|| ft_strncmp(t.tmp1, ".xpm", 5) != 0
		|| ft_strncmp(t.tmp2, ".xpm", 5) != 0
		|| ft_strncmp(t.tmp3, ".xpm", 5) != 0
		|| display->element_count != 6)
	{
		free_tex_map(display);
		ft_putstr_fd("Error\nSomething is wrong with the elements\n", 2);
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
