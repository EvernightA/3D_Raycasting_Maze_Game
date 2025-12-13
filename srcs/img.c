/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:41:21 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/13 14:30:47 by mratsima         ###   ########.fr       */
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
