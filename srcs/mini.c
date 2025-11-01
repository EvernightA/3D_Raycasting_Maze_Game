/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:38:12 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/01 16:07:19 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	mini_map(t_display *display, char **map)
{
	int i;
	int	j;

	i = 0;
	// print_map(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->texture.wall_img, j * SIZE_IMG, i * SIZE_IMG);	
			}
			else if (map[i][j] == '0')
			{
			}
			//else if (is_player(map[i][j]))
			//{
				//mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->texture.floor_img, j * SIZE_IMG, i * SIZE_IMG);
				// A FUNCTION TO PUT A PLAYER in pixel
				mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr, display->player.pixels.x * 1, display->player.pixels.y * 1, 0xFF00);
			
			//}
			j++;
		}
		i++;
	}
	// free_split(map);
}


