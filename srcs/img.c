/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:41:21 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/21 16:25:05 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

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

void    clear_img(t_display *display)
{
    if (display->all.addr)
        ft_memset(display->all.addr, 0, SCRN_HEIGHT * display->all.line_len);
}

void    clear_rays(t_display *display)
{
    if (display->rays.addr)
        ft_memset(display->rays.addr, 0, SCRN_HEIGHT * display->rays.line_len);
}