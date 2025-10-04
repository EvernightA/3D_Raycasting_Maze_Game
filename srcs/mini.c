/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:38:12 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/04 16:31:35 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	mini_map(t_display *display, char **map)
{
	int i;
	int	j;

	i = 0;
	//print_map(map);
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
				mlx_put_image_to_window(display->mlx.mlx_ptr, display->mlx.win_ptr, display->texture.floor_img, j * SIZE_IMG, i * SIZE_IMG);
			}
			else if (is_player(map[i][j]))
			{

			}
			j++;
		}
		i++;
	}
	free_split(map);
}


