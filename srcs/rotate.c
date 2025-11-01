/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:08:08 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/01 17:01:21 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int float_abs(float number)
{
    if (number < 0)
	{
		return (-number);
	}
	return (number);
}

void	rotate_player(t_display *display, float angle)
{
	float tmpx;
	float tmpy;
//
	tmpx = (display->end.x - display->begin.x) * cos(angle) - (display->end.y - display->begin.y) * sin(angle) + display->begin.x;
	tmpy = (display->end.y - display->begin.y) * cos(angle) + (display->end.x - display->begin.x) * sin(angle) + display->begin.y;
//
	display->end.x = float_abs(tmpx);
	display->end.y = float_abs(tmpy);
	//printf("end x = %d ; ", display->end.x);
	//printf("end y = %d\n\n", display->end.y);
	//mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr, tmpx, tmpy, 0XFF000);
}


//void	rotate_player(t_display *display, float angle)
//{
//	float tmpx;
//	float tmpy;
//	float dx;
//	float dy;

//	// Calculate the direction vector from player to laser endpoint
//	dx = display->end.x - display->begin.x;
//	dy = display->end.y - display->begin.y;
	
//	// Apply the correct 2D rotation formula
//	tmpx = dx * cos(angle) - dy * sin(angle) + display->begin.x;
//	tmpy = dx * sin(angle) + dy * cos(angle) + display->begin.y;

//	display->end.x = tmpx;
//	display->end.y = tmpy;
//	printf("end x = %d ; ", display->end.x);
//	printf("end y = %d\n\n", display->end.y);
//}