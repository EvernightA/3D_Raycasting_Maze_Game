/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:08:08 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/01 09:50:01 by fsamy-an         ###   ########.fr       */
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

	tmpx = 0.0;
	tmpy = 0.0;
	tmpx = (display->end.x - display->begin.x) * cos(angle) - (display->end.y - display->begin.y) * sin(angle) + display->begin.x;
	tmpy = (display->end.y - display->begin.y) * cos(angle) + (display->end.x - display->begin.x) * sin(angle) + display->begin.y;
	
	printf("rx = %f, ry= %f\n", tmpx, tmpy);
	display->end.x = fabs(tmpx);
	display->end.y = fabs(tmpy);
	display->end.f_x = fabs(tmpx);
	display->end.f_y = fabs(tmpy);
}

