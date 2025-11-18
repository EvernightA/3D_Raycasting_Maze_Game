/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:00:37 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/18 13:14:49 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		closed_error(char	**map)
{
	int i;
	int	j;
	int	k;

	i = 0;// columns
	j = 1;// columns
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

void	print_map(char **map)
{
	int i;

	i = 0;
	if (!map)
		return;
	while (map[i])
	{
		// printf("%s",map[i]);
		ft_putstr_fd(map[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int texture_error(t_display *display)
{
	char *tmp;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	tmp = ft_strnstr(display->texture.north, ".xpm", ft_strlen(display->texture.north));
	tmp1 = ft_strnstr(display->texture.south, ".xpm", ft_strlen(display->texture.south));
	tmp2 = ft_strnstr(display->texture.west, ".xpm", ft_strlen(display->texture.west));
	tmp3 = ft_strnstr(display->texture.east, ".xpm", ft_strlen(display->texture.east));
	if (tmp == NULL || tmp1 ==  NULL || tmp2 == NULL || tmp3 == NULL)
	{
		free(display->texture.c_rgb);
		free(display->texture.f_rgb);
		if (display->map)
			free_split(display->map);
		if (display->texture.dup_map)
			free_split(display->texture.dup_map);
		free(display->texture.east);
		free(display->texture.north);
		free(display->texture.south);
		free(display->texture.west);
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	if (ft_strncmp(tmp, ".xpm", 5) != 0 || ft_strncmp(tmp1, ".xpm", 5) != 0 
	|| ft_strncmp(tmp2, ".xpm", 5) != 0 || ft_strncmp(tmp3, ".xpm", 5) != 0)
 	{
		free(display->texture.c_rgb);
		free(display->texture.f_rgb);
		if (display->map)
			free_split(display->map);
		if (display->texture.dup_map)
			free_split(display->texture.dup_map);
		free(display->texture.east);
		free(display->texture.north);
		free(display->texture.south);
		free(display->texture.west);
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	return (0);
}

