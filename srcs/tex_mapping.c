/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:37:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/09 19:27:35 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	sample_texture(t_img_texture *img_tex, float u, float v)
{
	int		x;
	int		y;
	int		pixel;
	char	*addr;

	u = fmaxf(0.0f, fminf(1.0f, u));
	v = fmaxf(0.0f, fminf(1.0f, v));
	x = (int)(u * (img_tex->width - 1));
	y = (int)(v * (img_tex->height - 1));
	addr = img_tex->data + (y * img_tex->line_len + x * (img_tex->bpp / 8));
	pixel = *(unsigned int *)addr;
	return (pixel);
}

int	straight_line_case(int dx, int dy)
{
	if (dx > 0 && dy == 0)
	{
		return (WEST);
	}
	if (dx < 0 && dy == 0)
	{
		return (EAST);
	}
	if (dy > 0 && dx == 0)
	{
		return (NORTH);
	}
	if (dy < 0 && dx == 0)
	{
		return (SOUTH);
	}
	return (-1);
}

int	diagonal_line_direction(int dx, int dy, t_point collision_pixel)
{
	if (dx > 0 && dy > 0)
	{
		if (collision_pixel.x < collision_pixel.y)
			return (WEST);
	}
	if (dx < 0 && dy > 0)
	{
		if ((15 - collision_pixel.x) < collision_pixel.y)
			return (EAST);
	}
	if (dx > 0 && dy < 0)
	{
		if (collision_pixel.x < (15 - collision_pixel.y))
			return (WEST);
		else
			return (SOUTH);
	}
	if (dx < 0 && dy < 0)
	{
		if ((15 - collision_pixel.x) < (15 - collision_pixel.y))
			return (EAST);
		else
			return (SOUTH);
	}
	return (NORTH);
}

int	get_wall_direction(t_point collision, t_point player_bloc)
{
	t_point	collision_pixel;
	t_point	collision_bloc;
	int		dx;
	int		dy;

	collision_bloc.x = collision.x / 16;
	collision_bloc.y = collision.y / 16;
	collision_pixel.x = collision.x % 16;
	collision_pixel.y = collision.y % 16;
	dx = collision_bloc.x - player_bloc.x;
	dy = collision_bloc.y - player_bloc.y;
	if (straight_line_case(dx, dy) != -1)
		return (straight_line_case(dx, dy));
	else
		return (diagonal_line_direction(dx, dy, collision_pixel));
}
