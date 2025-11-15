/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:37:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/15 15:15:31 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    load_textures(t_display *display)
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
		exit(1);
	}
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

 int     sample_texture(t_img_texture *img_tex, float u, float v)
{
    int     x;
    int     y;
    int     pixel;
    char    *addr;
    
    x = (int)(u * (img_tex->width - 1));
    y = (int)(v * (img_tex->height - 1));
    
    addr = img_tex->data + (y * img_tex->line_len + x * (img_tex->bpp / 8));
    
    pixel = *(unsigned int *)addr;
    
    return (pixel);
}

int get_wall_direction_from_angle(float ray_angle)
{
    float angle;

	angle = fmod(ray_angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    
	else if (angle >= 3 * M_PI / 2 && angle < 2 * M_PI)
		return (NORTH);
	else if (angle >= M_PI / 2 && angle < M_PI)
			return (SOUTH);
    if (angle >= 0 && angle < M_PI / 2)
        return (EAST);
    else
        return (WEST);
}