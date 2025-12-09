/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:41:39 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/25 13:08:22 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	aff_floor_and_ceiling(t_display *display)
{
	int	i;
	int	j;
	int	ceiling_color;
	int	floor_color;

	j = 0;
	floor_color = create_trgb(0, display->texture.floor_rgb.red,
			display->texture.floor_rgb.green, display->texture.floor_rgb.blue);
	ceiling_color = create_trgb(0, display->texture.ceiling_rgb.red,
			display->texture.ceiling_rgb.green,
			display->texture.ceiling_rgb.blue);
	while (j < SCRN_HEIGHT - 1)
	{
		i = 0;
		while (i < SCRN_WIDTH - 1)
		{
			if (j <= SCRN_HEIGHT / 2)
				img_pix_put(&display->all, i, j, ceiling_color);
			else
				img_pix_put(&display->all, i, j, floor_color);
			i++;
		}
		j++;
	}
}
