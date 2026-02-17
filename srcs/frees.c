/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:22:27 by mratsima          #+#    #+#             */
/*   Updated: 2026/02/17 10:14:55 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_abs(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	free_texture(t_display *display)
{
	free_split(display->map);
	free(display->texture.c_rgb);
	free(display->texture.f_rgb);
	free(display->texture.east);
	free(display->texture.north);
	free(display->texture.west);
	free(display->texture.south);
}

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
