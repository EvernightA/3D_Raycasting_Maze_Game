/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:26:50 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 13:17:27 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Load XPM Textures - Getting Your Wall Pictures Ready! 🖼️
 *
 * Imagine you have a bunch of wallpaper rolls for your room. Before you can
 * put them up, you need to unroll them and get them ready. That's what this
 * function does for your game walls!
 *
 * It takes the picture files you specified (north, south, east, west walls)
 * and loads them into the computer's memory so the game can use them.
 * Each picture becomes a special "texture" that the computer can show on walls.
 *
 * If any picture can't be loaded (like if the file is missing), it tells you
 * there's a problem and stops the game.
 *
 * @param display Where all your game pictures and settings are stored
 */
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

/**
 * @brief Get Texture Data - Unlocking the Picture Secrets! 🔓
 *
 * Now that you have your wallpaper rolls ready, you need to open them up
 * and see what's inside! This function takes each loaded picture and
 * gets the actual colors and pixels that make up the image.
 *
 * It's like taking a photograph and finding out what color each tiny
 * dot should be. The computer stores this information so it can quickly
 * grab colors when drawing walls.
 *
 * @param display Where all your game pictures and settings are stored
 */
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
