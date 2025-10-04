/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:27:43 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/04 14:29:23 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_initialization(t_display *display)
{
	int x;
	int y;

	display->texture.wall_img = mlx_xpm_file_to_image(display->mlx.mlx_ptr,"./textures/f.xpm", &x, &y);
	display->texture.floor_img = mlx_xpm_file_to_image(display->mlx.mlx_ptr,"./textures/w.xpm", &x, &y);
}
