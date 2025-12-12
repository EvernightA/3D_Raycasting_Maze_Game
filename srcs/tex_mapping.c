/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:33 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 13:17:28 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Grab a Color from Your Wallpaper! 🎨
 *
 * Imagine you have a big wallpaper with lots of pretty colors. When you want
 * to paint a wall, you need to pick just the right color from the right spot
 * on the wallpaper. That's what this function does!
 *
 * It takes coordinates (like "3 steps across, 5 steps up") and finds the
 * color at that exact spot on the texture. If you ask for a spot outside
 * the wallpaper, it just uses the closest edge color instead.
 *
 * It's like having a magic color-picker that never misses the wallpaper!
 *
 * @param img_tex The wallpaper (texture) you're picking colors from
 * @param tex_x How far across the wallpaper (left to right)
 * @param tex_y How far up the wallpaper (bottom to top)
 * @return The color number at that spot on the wallpaper
 */
int	sample_texture(t_img_texture *img_tex, int tex_x, int tex_y)
{
	char	*addr;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img_tex->width)
		tex_x = img_tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= img_tex->height)
		tex_y = img_tex->height - 1;
	addr = img_tex->data + (tex_y * img_tex->line_len
			+ tex_x * (img_tex->bpp / 8));
	return (*(unsigned int *)addr);
}

/**
 * @brief Pick the Right Wallpaper for Each Wall! 🧭
 *
 * Imagine you're decorating a room and each wall needs different wallpaper.
 * The north wall gets stripes, the south wall gets flowers, etc. This function
 * is like your decorator helper that knows which wallpaper goes where!
 *
 * Based on which direction the wall is facing (north, south, east, west),
 * it picks the matching texture. It's like having a smart assistant that
 * always chooses the right wallpaper roll for each wall.
 *
 * @param display Your whole room setup with all the wallpapers
 * @param wall_dir Which way the wall is facing (like a compass: N, S, E, W)
 * @return The perfect wallpaper roll for that wall direction
 */
t_img_texture	*get_texture_for_wall(t_display *display, int wall_dir)
{
	if (wall_dir == NORTH)
		return (&display->texture.t_north);
	else if (wall_dir == SOUTH)
		return (&display->texture.t_south);
	else if (wall_dir == EAST)
		return (&display->texture.t_east);
	else
		return (&display->texture.t_west);
}
