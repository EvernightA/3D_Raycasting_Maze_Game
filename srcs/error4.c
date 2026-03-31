/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:36:20 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/08 13:57:14 by fsamy-an         ###   ########.fr       */
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

int	is_unknown(char c)
{
	if (!(is_player(c)) && c != '0' && c != '1' && c != ' ' && c != '\n')
	{
		return (1);
	}
	return (0);
}

int	player_error(int count, t_display *display)
{
	if (count == 0)
	{
		ft_putstr_fd("Error\nNo player found in the map\n", 2);
		free_tex_map(display);
		return (1);
	}
	else if (count > 1)
	{
		ft_putstr_fd("Error\nMultiple player found\n", 2);
		free_tex_map(display);
		return (1);
	}
	return (0);
}

int	player_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_player(str[i]) || str[i] == '0')
			return (1);
		i++;
	}
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
