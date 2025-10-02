/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:00:37 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/02 22:33:07 by fsamy-an         ###   ########.fr       */
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
	while (map[i])
	{
		printf("%s",map[i]);
		i++;
	}
}

int texture_error(t_tex *texture)
{
	char *tmp;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	tmp = ft_strnstr(texture->north, ".xpm", ft_strlen(texture->north));
	tmp1 = ft_strnstr(texture->south, ".xpm", ft_strlen(texture->south));
	tmp2 = ft_strnstr(texture->west, ".xpm", ft_strlen(texture->west));
	tmp3 = ft_strnstr(texture->east, ".xpm", ft_strlen(texture->east));
	if (tmp == NULL || tmp1 ==  NULL || tmp2 == NULL || tmp3 == NULL)
	{
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	if (ft_strncmp(tmp, ".xpm", 5) != 0 || ft_strncmp(tmp1, ".xpm", 5) != 0 
	|| ft_strncmp(tmp2, ".xpm", 5) != 0 || ft_strncmp(tmp3, ".xpm", 5) != 0)
 	{
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	return (0);
}

