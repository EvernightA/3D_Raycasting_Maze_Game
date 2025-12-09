/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   west_fix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:34:25 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/09 18:35:43 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	west_north_case(float normalised_x, t_hit *hit, t_point bloc,
		t_display *display)
{
	int wall_above;
	int wall_below;
	int wall_left;

	if (display->map[bloc.y][bloc. x - 1] != '1')
	{
		wall_above = (display->map[bloc.y - 1][bloc. x] == '1');
		wall_below = (display->map[bloc.y + 1][bloc.x] == '1');
		wall_left = (display->map[bloc.y][bloc.x - 1] == '1');
		if (abs(bloc.x - display->player. blocs.x) < 2
			&& ! wall_above && !wall_left && normalised_x >= 0.3f && normalised_x <= 1.0f)
			return;
		if ((wall_above || wall_below) && normalised_x <= 1.0f)
			hit->wall_direction = WEST;
		else if (normalised_x <= 1.0f)
			hit->wall_direction = WEST;
	}
}

static void	west_south_case(float normalised_x, t_hit *hit, t_point bloc,
		t_display *display)
{
	int wall_above;
	int wall_below;
	int wall_left;

	if (display->map[bloc.y][bloc.x - 1] != '1')
	{
		wall_above = (display->map[bloc.y - 1][bloc.x] == '1');
		wall_below = (display->map[bloc.y + 1][bloc. x] == '1');
		wall_left = (display->map[bloc.y][bloc.x - 1] == '1');
		if (abs(bloc. x - display->player.blocs.x) < 2
			&& !wall_below && ! wall_left && normalised_x >= 0.3f && normalised_x <= 1.0f)
			return;
		if ((wall_above || wall_below) && normalised_x <= 1.0f)
			hit->wall_direction = WEST;
		else if (normalised_x <= 1.0f)
			hit->wall_direction = WEST;
	}
}

void	west_case(float normalised_x, t_hit *hit, t_point bloc,
		t_display *display)
{
	int dx;
	int dy;

	dx = (int)(hit->collision.f_x / 16) - display->player.blocs.x;
	dy = (int)(hit->collision.f_y / 16) - display->player.blocs.y;

	if (dx > 0 && dy > 0 && hit->wall_direction == NORTH)
		west_north_case(normalised_x, hit, bloc, display);
	else if (dx > 0 && dy < 0 && hit->wall_direction == SOUTH)
		west_south_case(normalised_x, hit, bloc, display);
}
