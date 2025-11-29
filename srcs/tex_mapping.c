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

static int	get_tex_pixel(t_img_texture *img_tex, int x, int y)
{
	char	*addr;

	if (x < 0)
		x = 0;
	if (x >= img_tex->width)
		x = img_tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= img_tex->height)
		y = img_tex->height - 1;
	addr = img_tex->data + (y * img_tex->line_len + x * (img_tex->bpp / 8));
	return (*(unsigned int *)addr);
}

static int	lerp_color(int c1, int c2, float t)
{
	float	inv_t;
	int		a;
	int		r;
	int		g;
	int		b;

	inv_t = 1.0f - t;
	a = (int)(((c1 >> 24) & 0xFF) * inv_t + ((c2 >> 24) & 0xFF) * t);
	r = (int)(((c1 >> 16) & 0xFF) * inv_t + ((c2 >> 16) & 0xFF) * t);
	g = (int)(((c1 >> 8) & 0xFF) * inv_t + ((c2 >> 8) & 0xFF) * t);
	b = (int)((c1 & 0xFF) * inv_t + (c2 & 0xFF) * t);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

int	sample_texture(t_img_texture *img_tex, float u, float v)
{
	float	tx;
	float	ty;
	int		x0;
	int		y0;
	float	fx;
	float	fy;
	int		c00;
	int		c10;
	int		c01;
	int		c11;
	int		c0;
	int		c1;

	tx = u * (img_tex->width - 1);
	ty = v * (img_tex->height - 1);
	x0 = (int)tx;
	y0 = (int)ty;
	fx = tx - x0;
	fy = ty - y0;
	c00 = get_tex_pixel(img_tex, x0, y0);
	c10 = get_tex_pixel(img_tex, x0 + 1, y0);
	c01 = get_tex_pixel(img_tex, x0, y0 + 1);
	c11 = get_tex_pixel(img_tex, x0 + 1, y0 + 1);
	c0 = lerp_color(c00, c10, fx);
	c1 = lerp_color(c01, c11, fx);
	return (lerp_color(c0, c1, fy));
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

int diagonal_line_direction(int dx, int dy, t_point collision_pixel)
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

int get_wall_direction(t_point collision, t_point player_bloc)
{
	t_point	collision_pixel;
	t_point	collision_bloc;
	int dx;
	int dy;

    collision_bloc.x = collision.x / 16;
    collision_bloc.y = collision.y / 16;
    collision_pixel.x = collision.x % 16;
    collision_pixel.y = collision.y % 16;  
	// just get the coordinates of the vector player->wall 
	// so we can know which direction the ray has
	dx = collision_bloc.x - player_bloc.x;
	dy = collision_bloc.y - player_bloc.y;    
	if (straight_line_case(dx, dy) != -1)
		return (straight_line_case(dx, dy));
    // For diagonal hits, determine by which edge is closer
	else
		return (diagonal_line_direction(dx, dy, collision_pixel));
}
