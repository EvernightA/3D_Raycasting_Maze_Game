/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:28:34 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/02 22:18:57 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


int	is_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
	{
		return (1);
	}
	return (0);
}
static int	is_unknown(char c)
{
	if (!(is_player(c)) && c != '0' && c != '1' && c != ' ' && c != '\n')
	{
		return (1);
	}
	return (0);
}

static int	player_error(int count)
{
	if (count == 0)
	{
		ft_putstr_fd("Error\nNo player found in the map\n", 2);
		return (1);
	}
	else if (count > 1)
	{
		ft_putstr_fd("Error\nMultiple player found\n", 2);
		return (1);
	}
	return (0);
}

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

int	multiple_player_check(t_tex *texture)
{
	int		i;
	int		j;
	int			count;

	i = 0;
	count = 0;
	while (texture->map[i])
	{
		j = 0;
		while (texture->map[i][j])
		{
			if (is_unknown(texture->map[i][j]))
			{
				ft_putstr_fd("Error\nUnknown character \'", 2);
				ft_putchar_fd(texture->map[i][j], 2);
				ft_putstr_fd("\' found in the map\n", 2);
				return (1);
			}
			if (is_player(texture->map[i][j]))
				count++;
			j++;
		}
		if (closed__map_error(texture->map[i]))
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

int	matrix_height(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

int player_in_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_player(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	error_handling(t_tex *texture)
{
	char	**tmp;

	if (multiple_player_check(texture) || texture_error(texture))
		return (1);
	tmp = dup_mat(texture->map_height, texture->map);
	print_map(tmp);
	if (matrix_height(tmp) <= 2)
	{
		ft_putstr_fd("Error\nWhat kind of psych are u?\n", 2);
		free_split(tmp);
		return (1);
	}
	if (closed_error(tmp))
	{
		free_split(tmp);
		ft_putstr_fd("Error1\nUnclosed wall found\n", 2);
		return (1);
	}
	free_split(tmp);
	return (0);
}
