/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:41:21 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/09 08:57:17 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (img->addr)
	{
		if (x < 0 || y < 0 || x >= SCRN_WIDTH || y >= SCRN_HEIGHT)
		{
			return ;
		}
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

void	clear_img(t_display *display)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCRN_HEIGHT)
	{
		j = 0;
		while (j < SCRN_WIDTH)
		{
			img_pix_put(&display->all, j, i, 0x00000);
			j++;
		}
		i++;
	}
}

void	clear_rays(t_display *display)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCRN_HEIGHT)
	{
		j = 0;
		while (j < SCRN_WIDTH)
		{
			img_pix_put(&display->rays, j, i, 0x00000);
			j++;
		}
		i++;
	}
}
