/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:41:21 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/08 20:08:16 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

void    clear_img(t_img *img)
{
    int i;
    int j;

    i = 0;
    while (i < SCRN_HEIGHT)
    {
        j = 0;
        while (j < SCRN_WIDTH)
        {
            img_pix_put(img ,j , i, 0x0000000);
            j++;
        }
        i++;
    }
}