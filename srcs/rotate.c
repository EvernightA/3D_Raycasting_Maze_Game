/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:08:08 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/21 09:58:18 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate_player(t_display *display, float angle)
{
	float tmpx;
	float tmpy;

	tmpx = (display->end.x - display->begin.x) * cos(angle) - (display->end.y - display->begin.y) * sin(angle) + display->begin.x;
	tmpy = (display->end.y - display->begin.y) * cos(angle) + (display->end.x - display->begin.x) * sin(angle) + display->begin.y;

	display->end.x = tmpx;
	display->end.y = tmpy;
}