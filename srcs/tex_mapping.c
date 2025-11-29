/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:37:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/22 10:20:20 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    init_xpm_image(t_display *display)
{
    display->texture.t_north.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.north, 
        &display->texture.t_north.width, &display->texture.t_north.height);

	display->texture.t_south.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.south, 
        &display->texture.t_south.width, &display->texture.t_south.height);
	
	display->texture.t_east.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.east, 
        &display->texture.t_east.width, &display->texture.t_east.height);

	display->texture.t_west.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.west, 
        &display->texture.t_west.width, &display->texture.t_west.height);

    if (!display->texture.t_north.img_ptr
		|| !display->texture.t_south.img_ptr
		|| !display->texture.t_east.img_ptr
		|| !display->texture.t_west.img_ptr)
	{
		ft_putstr_fd("Error\nCouldn't load texture\n", 2);
		/*all exit should change into a function that frees everything before exit */
        exit(1);
	}
}

void    load_textures(t_display *display)
{
    init_xpm_image(display);
    display->texture.t_north.data = mlx_get_data_addr(
        display->texture.t_north.img_ptr, 
        &display->texture.t_north.bpp,
        &display->texture.t_north.line_len, 
        &display->texture.t_north.endian);
	
	display->texture.t_south.data = mlx_get_data_addr(
        display->texture.t_south.img_ptr, 
        &display->texture.t_south.bpp,
        &display->texture.t_south.line_len, 
        &display->texture.t_south.endian);
	
	display->texture.t_east.data = mlx_get_data_addr(
        display->texture.t_east.img_ptr, 
        &display->texture.t_east.bpp,
        &display->texture.t_east.line_len, 
        &display->texture.t_east.endian);
	
	display->texture.t_west.data = mlx_get_data_addr(
        display->texture.t_west.img_ptr, 
        &display->texture.t_west.bpp,
        &display->texture.t_west.line_len, 
        &display->texture.t_west.endian);
}

int	sample_texture(t_img_texture *img_tex, float u, float v)
{
	int		x;
	int		y;
	int		pixel;
	char	*addr;

	if (u < 0.0f)
		u = 0.0f;
	if (u > 1.0f)
		u = 1.0f;
	if (v < 0.0f)
		v = 0.0f;
	if (v > 1.0f)
		v = 1.0f;
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

int	diagonal_line_direction(int dx, int dy, float pixel_x, float pixel_y)
{
	if (dx > 0 && dy > 0)
	{
		if (pixel_x < pixel_y)
			return (WEST);
	}
	if (dx < 0 && dy > 0)
	{
		if ((SIZE_IMG - pixel_x) < pixel_y)
			return (EAST);
	}
	if (dx > 0 && dy < 0)
	{
		if (pixel_x < (SIZE_IMG - pixel_y))
			return (WEST);
		else
			return (SOUTH);
	}
	if (dx < 0 && dy < 0)
	{
		if ((SIZE_IMG - pixel_x) < (SIZE_IMG - pixel_y))
			return (EAST);
		else
			return (SOUTH);
	}
	return (NORTH);
}

int	get_wall_direction(t_point collision, t_point player_bloc)
{
	float	pixel_x;
	float	pixel_y;
	int		collision_bloc_x;
	int		collision_bloc_y;
	int		dx;
	int		dy;

	collision_bloc_x = (int)(collision.f_x / SIZE_IMG);
	collision_bloc_y = (int)(collision.f_y / SIZE_IMG);
	pixel_x = fmodf(collision.f_x, SIZE_IMG);
	pixel_y = fmodf(collision.f_y, SIZE_IMG);
	if (pixel_x < 0.0f)
		pixel_x += SIZE_IMG;
	if (pixel_y < 0.0f)
		pixel_y += SIZE_IMG;
	dx = collision_bloc_x - player_bloc.x;
	dy = collision_bloc_y - player_bloc.y;
	if (straight_line_case(dx, dy) != -1)
		return (straight_line_case(dx, dy));
	else
		return (diagonal_line_direction(dx, dy, pixel_x, pixel_y));
}
