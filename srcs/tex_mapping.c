/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:37:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/15 13:56:10 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    load_textures(t_display *display)
{
    display->texture.t_north.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.north, 
        &display->texture.t_north.width, &display->texture.t_north.height);
	if (!display->texture.t_north.img_ptr)
	{
		ft_putstr_fd("Error\nCouldn't load texture\n", 2);
		exit(1);
	}
	display->texture.t_south.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.south, 
        &display->texture.t_south.width, &display->texture.t_south.height);
	
	display->texture.t_east.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.east, 
        &display->texture.t_east.width, &display->texture.t_east.height);

	display->texture.t_west.img_ptr = mlx_xpm_file_to_image(
        display->mlx.mlx_ptr, display->texture.west, 
        &display->texture.t_west.width, &display->texture.t_west.height);
    
    // Get texture data pointer for direct access
    display->texture.t_north.data = mlx_get_data_addr(
        display->texture.t_north.img_ptr, 
        &display->texture.t_north.bpp,
        &display->texture.t_north.line_len, 
        &display->texture.t_north.endian);
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