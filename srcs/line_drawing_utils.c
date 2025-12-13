/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:38:28 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 14:34:39 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_texture(t_img_texture **texture_to_display, t_hit hit,
		t_display *display)
{
	(void)texture_to_display;
	if (hit.wall_direction == NORTH)
		*texture_to_display = &display->texture.t_north;
	else if (hit.wall_direction == SOUTH)
		*texture_to_display = &display->texture.t_south;
	else if (hit.wall_direction == EAST)
		*texture_to_display = &display->texture.t_east;
	else
		*texture_to_display = &display->texture.t_west;
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

void	draw_textured_line(t_line *line, t_hit hit, int line_size,
		t_display *display)
{
	t_tex_utils	utils;
	int			tex_x;
	int			tex_y;
	int			texture_color;

	if (line_size <= 0)
		return;
	utils.tmp = line;
	utils.count = 0;
	utils.texture_to_display = &display->texture.t_north;
	set_texture(&utils.texture_to_display, hit, display);
	while (utils.tmp)
	{
		float uv_y = (float)utils.count / line_size;
		tex_x = calculate_tex_x(&display->ray, utils.texture_to_display);
		tex_y = (int)(uv_y * (float)utils.texture_to_display->height);
		texture_color = sample_texture(utils.texture_to_display, tex_x, tex_y);
		img_pix_put(&display->all, utils.tmp->dot.x, utils.tmp->dot.y,
			texture_color);
		utils.count++;
		utils.tmp = utils.tmp->next;
	}
}
