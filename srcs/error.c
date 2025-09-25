/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:28:34 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 11:50:02 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


static int	is_player(char c)
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
				ft_putstr_fd("Error\nUnknown character found in the map\n", 2);
				printf("|%c|", texture->map[i][j]);
				return (1);
			}
			if (is_player(texture->map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (player_error(count))
		return (1);
	return (0);
}

int	error_handling(t_tex *texture)
{
	if (multiple_player_check(texture))
	{
		return (1);
	}
	return (0);
}