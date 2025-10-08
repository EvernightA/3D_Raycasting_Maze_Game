/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:27:43 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/04 16:40:31 by mratsima         ###   ########.fr       */
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
