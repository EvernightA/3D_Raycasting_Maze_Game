/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:08:08 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/22 09:38:29 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate_player(t_display *display, float angle)
{
	float tmpx;
	float tmpy;

	tmpx = (display->begin.x - display->end.x) * cos(angle) - (display->begin.y - display->end.y) * sin(angle) + display->begin.x;
	tmpy = (display->begin.y - display->end.y) * cos(angle) + (display->begin.x - display->end.x) * sin(angle) + display->begin.y;

	display->end.x = tmpx;
	display->end.y = tmpy;
	mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr, tmpx, tmpy, 0XFF000);
}