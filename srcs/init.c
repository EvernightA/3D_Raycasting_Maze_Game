/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:27:43 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/08 19:46:29 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_initialization(t_display *display)
{
	int x;
	int y;

	display->texture.wall_img = mlx_xpm_file_to_image(display->mlx.mlx_ptr,"./textures/f.xpm", &x, &y);
	display->texture.floor_img = mlx_xpm_file_to_image(display->mlx.mlx_ptr,"./textures/w.xpm", &x, &y);
	display->all.mlx_img = mlx_new_image(display->mlx2.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT);
	display->rays.mlx_img = mlx_new_image(display->mlx.mlx_ptr, SCRN_WIDTH, SCRN_HEIGHT);
	if (!display->all.mlx_img || !display->rays.mlx_img)
		return ;
	display->all.addr = mlx_get_data_addr(display->all.mlx_img, &display->all.bpp, &display->all.line_len, &display->all.endian);
	display->rays.addr = mlx_get_data_addr(display->rays.mlx_img, &display->rays.bpp, &display->rays.line_len, &display->rays.endian);
}
