/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 13:17:27 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Measure How Big Your Wall Slice Should Be! 📏
 *
 * Imagine you're cutting a piece of cake. The farther away the cake is,
 * the smaller slice you get, right? This function figures out how tall
 * a wall should look on your screen based on how far away it is.
 *
 * It also decides where on the screen to put the wall - right in the middle,
 * from floor to ceiling. If the wall would go off the top or bottom of your
 * screen, it trims it so it fits perfectly.
 *
 * The function fixes a special "fish-eye" problem where things look curved
 * when they should be straight, by using a math trick with angles.
 *
 * @param ray Your laser pointer showing how far away the wall is
 * @param draw_start Where to start painting the wall (from the top)
 * @param draw_end Where to stop painting the wall (to the bottom)
 * @param line_height How tall the wall should be on your screen
 */
static void	calculate_line_bounds(t_ray *ray, int *draw_start, int *draw_end,
				int *line_height)
{
	float	corrected_dist;

	corrected_dist = ray->perp_wall_dist * cosf(ray->angle_offset);
	if (corrected_dist > 0)
		*line_height = (int)(SCRN_HEIGHT / corrected_dist);
	else
		*line_height = SCRN_HEIGHT;
	*draw_start = -(*line_height) / 2 + SCRN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + SCRN_HEIGHT / 2;
	if (*draw_end >= SCRN_HEIGHT)
		*draw_end = SCRN_HEIGHT - 1;
}

/**
 * @brief Figure Out Where to Look on the Wallpaper! 📍
 *
 * Imagine you're painting a wall and you need to copy a pattern from wallpaper.
 * But the wall is taller than the wallpaper is wide, so you have to wrap it
 * around. This function figures out exactly which part of the wallpaper
 * pattern should go on your wall.
 *
 * It takes where you hit the wall and calculates "how far along the wallpaper
 * should I look?" Sometimes it flips the pattern if you're looking at the
 * wall from the other side (like seeing the back of the wallpaper).
 *
 * It's like having a magic map that tells you "for this spot on the wall,
 * copy this exact spot from the wallpaper!"
 *
 * @param ray Your laser pointer showing where you hit the wall
 * @param tex The wallpaper you're copying from
 * @return Where to look on the wallpaper (left to right position)
 */
static int	calculate_tex_x(t_ray *ray, t_img_texture *tex)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

/**
 * @brief Paint a Strip of Wall with Pretty Wallpaper! 🎨
 *
 * Imagine you're decorating a long wall, but you do it one tiny section at a time.
 * This function paints just one vertical sliver of wall (like a candy cane stripe)
 * at a specific spot on your screen.
 *
 * It figures out:
 * - Which wallpaper to use for this wall
 * - How tall the stripe should be (based on how far away you are)
 * - Where on the screen to paint it
 * - Which part of the wallpaper to copy for each pixel
 *
 * It's like having a tiny painter robot that carefully copies wallpaper
 * patterns onto your 3D walls, one stripe at a time!
 *
 * @param display Your whole 3D world with walls and wallpapers
 * @param x Which column on the screen to paint (like 100th pixel from the left)
 * @param ray Your laser pointer showing exactly where and how far the wall is
 */
void	draw_wall_stripe(t_display *display, int x, t_ray *ray)
{
	t_img_texture	*tex;
	t_draw_utils	draw;

	tex = get_texture_for_wall(display, ray->wall_dir);
	calculate_line_bounds(ray, &draw.draw_start,
		&draw.draw_end, &draw.line_height);
	draw.tex_x = calculate_tex_x(ray, tex);
	draw.step = (float)tex->height / (float)draw.line_height;
	draw.tex_pos = (draw.draw_start - SCRN_HEIGHT / 2 + draw.line_height / 2)
		* draw.step;
	draw.y = draw.draw_start;
	while (draw.y < draw.draw_end)
	{
		draw.tex_y = (int)draw.tex_pos;
		if (draw.tex_y >= tex->height)
			draw.tex_y = tex->height - 1;
		draw.tex_pos += draw.step;
		draw.color = sample_texture(tex, draw.tex_x, draw.tex_y);
		img_pix_put(&display->all, x, draw.y, draw.color);
		draw.y++;
	}
}

void	cast_all_rays(t_display *display)
{
	t_ray	ray;
	float	angle;
	int		x;

	x = 0;
	while (x < SCRN_WIDTH)
	{
		angle = -FOV / 2.0f + ((float)x / (float)SCRN_WIDTH) * FOV;
		cast_single_ray(display, &ray, angle);
		draw_wall_stripe(display, x, &ray);
		x++;
	}
}
