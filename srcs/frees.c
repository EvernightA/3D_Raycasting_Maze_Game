/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:22:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/10/04 14:18:48 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	free_split(display->texture.map);
	free(display->texture.c_rgb);
	free(display->texture.f_rgb);
	free(display->texture.east);
	free(display->texture.north);
	free(display->texture.west);
	free(display->texture.south);
}

