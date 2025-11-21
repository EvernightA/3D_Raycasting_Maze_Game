/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:41:39 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/21 15:52:34 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void	aff_floor_and_ceiling(t_display *display)
{
	int i;
	int j;
	int ceiling_color;
	int floor_color;
	int half_height;

	floor_color = create_trgb(0, display->texture.floor_rgb.red,
		display->texture.floor_rgb.green, display->texture.floor_rgb.blue);
	ceiling_color = create_trgb(0, display->texture.ceiling_rgb.red,
		display->texture.ceiling_rgb.green, display->texture.ceiling_rgb.blue);
	half_height = SCRN_HEIGHT >> 1;
	j = 0;
	while (j < half_height)
	{
		i = 0;
		while (i < SCRN_WIDTH)
		{
			img_pix_put(&display->all, i, j, ceiling_color);
			img_pix_put(&display->all, i, j + half_height, floor_color);
			i++;
		}
		j++;
	}
}
