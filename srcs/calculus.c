/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:17:26 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/12 11:16:59 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	shifter(int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (pow(2, i) == number)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

t_point	calculate_end(t_point begin, float angle, int max_distance)
{
	t_point	end;

	end.x = begin.x + cos(angle) * max_distance;
	end.y = begin.y + sin(angle) * max_distance;
	end.f_x = begin.f_x + cos(angle) * max_distance;
	end.f_y = begin.f_y + sin(angle) * max_distance;
	return (end);
}

void	calculus_dir(t_display *display)
{
	display->player.delta_x = cos(display->player.angle) * SPEED;
	display->player.delta_y = sin(display->player.angle) * SPEED;
	display->player.perp_x = -display->player.delta_y;
	display->player.perp_y = display->player.delta_x;
}

float	to_wall(t_display *display, t_point collision, float beta)
{
	float	distance;
	float	dx;
	float	dy;

	dx = display->player.pixels.f_x - collision.f_x;
	dy = display->player.pixels.f_y - collision.f_y;
	distance = sqrtf(dx * dx + dy * dy);
	distance = distance * cosf(beta);
	return (distance);
}
