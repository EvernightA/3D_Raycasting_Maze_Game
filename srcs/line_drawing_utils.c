/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/12 12:45:14 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
