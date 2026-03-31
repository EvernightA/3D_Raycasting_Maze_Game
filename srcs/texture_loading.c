/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:26:50 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/09 19:27:42 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_xpm_image(t_display *display)
{
	display->texture.t_north.img_ptr = mlx_xpm_file_to_image(
			display->mlx2.mlx_ptr, display->texture.north,
			&display->texture.t_north.width, &display->texture.t_north.height);
	display->texture.t_south.img_ptr = mlx_xpm_file_to_image(
			display->mlx2.mlx_ptr, display->texture.south,
			&display->texture.t_south.width, &display->texture.t_south.height);
	display->texture.t_east.img_ptr = mlx_xpm_file_to_image(
			display->mlx2.mlx_ptr, display->texture.east,
			&display->texture.t_east.width, &display->texture.t_east.height);
	display->texture.t_west.img_ptr = mlx_xpm_file_to_image(
			display->mlx2.mlx_ptr, display->texture.west,
			&display->texture.t_west.width, &display->texture.t_west.height);
	if (!display->texture.t_north.img_ptr || !display->texture.t_south.img_ptr
		|| !display->texture.t_east.img_ptr || !display->texture.t_west.img_ptr)
	{
		ft_putstr_fd("Error\nCouldn't load texture\n", 2);
		quit_win(display);
	}
}

void	load_textures(t_display *display)
{
	init_xpm_image(display);
	display->texture.t_north.data = mlx_get_data_addr(
			display->texture.t_north.img_ptr,
			&display->texture.t_north.bpp, &display->texture.t_north.line_len,
			&display->texture.t_north.endian);
	display->texture.t_south.data = mlx_get_data_addr(
			display->texture.t_south.img_ptr,
			&display->texture.t_south.bpp, &display->texture.t_south.line_len,
			&display->texture.t_south.endian);
	display->texture.t_east.data = mlx_get_data_addr(
			display->texture.t_east.img_ptr,
			&display->texture.t_east.bpp, &display->texture.t_east.line_len,
			&display->texture.t_east.endian);
	display->texture.t_west.data = mlx_get_data_addr(
			display->texture.t_west.img_ptr,
			&display->texture.t_west.bpp, &display->texture.t_west.line_len,
			&display->texture.t_west.endian);
}
