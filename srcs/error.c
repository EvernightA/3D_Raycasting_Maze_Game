/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:28:34 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/08 07:53:40 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		closed__map_error(char *str)
{
	if (ft_strnstr(str, " 0", ft_strlen(str)) || ft_strnstr(str, "0 ", ft_strlen(str))
	|| ft_strnstr(str, "0\n", ft_strlen(str)) || ft_strnstr(str, "\n0", ft_strlen(str))
	|| ft_strnstr(str, "\t0", ft_strlen(str)) || ft_strnstr(str, "0\t", ft_strlen(str))
	|| ft_strnstr(str, "0N ",ft_strlen(str)) || ft_strnstr(str, "0E ", ft_strlen(str))
	|| ft_strnstr(str, "0S ",ft_strlen(str)) || ft_strnstr(str, "0W ", ft_strlen(str))
	|| ft_strnstr(str, "0N\n",ft_strlen(str)) || ft_strnstr(str, "0E\n", ft_strlen(str))
	|| ft_strnstr(str, "0S\n",ft_strlen(str)) || ft_strnstr(str, "0W\n", ft_strlen(str))
	|| ft_strnstr(str, "0N\t",ft_strlen(str)) || ft_strnstr(str, "0E\t", ft_strlen(str))
	|| ft_strnstr(str, "0S\t",ft_strlen(str)) || ft_strnstr(str, "0W\t", ft_strlen(str))
	|| ft_strnstr(str, "N ",ft_strlen(str)) || ft_strnstr(str, "E ", ft_strlen(str))
	|| ft_strnstr(str, "S ",ft_strlen(str)) || ft_strnstr(str, "W ", ft_strlen(str))
	|| ft_strnstr(str, "N\n",ft_strlen(str)) || ft_strnstr(str, "E\n", ft_strlen(str))
	|| ft_strnstr(str, "S\n",ft_strlen(str)) || ft_strnstr(str, "W\n", ft_strlen(str))
	|| str[ft_strlen(str) - 1] == '0'
)

	{
		return (1);
	}
	return (0);
}

int	multiple_player_check(t_display *display)
{
	int		i;
	int		j;
	int			count;

	i = 0;
	count = 0;
	while (display->map[i])
	{
		j = 0;
		while (display->map[i][j])
		{
			if (is_unknown(display->map[i][j]))
			{
				ft_putstr_fd("Error\nUnknown character \'", 2);
				ft_putchar_fd(display->map[i][j], 2);
				ft_putstr_fd("\' found in the map\n", 2);
				return (1);
			}
			if (is_player(display->map[i][j]))
				count++;
			j++;
		}
		if (closed__map_error(display->map[i]))
		{
			ft_putstr_fd("Error\nUnclosed map found\n", 2);
			return (1);
		}
		i++;
	}
	if (player_error(count))
		return (1);
	return (0);
}

int	error_handling(t_display *display)
{
	char	**tmp;

	if (multiple_player_check(display) || texture_error(display))
		return (1);
	tmp = dup_mat(display->texture.map_height, display->map);
	display->texture.dup_map = dup_mat(display->texture.map_height, display->map);
	if (matrix_height(tmp) <= 2)
	{
		ft_putstr_fd("Error\nWhat kind of psych are u?\n", 2);
		free_split(tmp);
		return (1);
	}
	if (closed_error(tmp))
	{
		free_split(tmp);
		ft_putstr_fd("Error\nUnclosed wall found\n", 2);
		return (1);
	}
	free_split(tmp);
	return (0);
}
