/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:37:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 11:57:54 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
