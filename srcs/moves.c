/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:41:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/19 08:49:23 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	clean_rendering(t_display *display)
{
	clear_img(display);
   	clear_rays(display);
	render_all(display);
}

int releasing_key(int key, void *param)
{
    t_display  *display;

    display = (t_display *)param;
    (void)display;
    if (key == XK_W || key == XK_w)
    {
        display->key_stat.w_press = false;
        printf("W released\n");
    }
    if (key == XK_A || key == XK_a)
    {
        display->key_stat.a_press = false;
        printf("A released\n");

    }
    if (key == XK_S || key == XK_s)
    {
        display->key_stat.s_press = false;
        printf("S released\n");

    }
    if (key == XK_D || key == XK_d)
    {
        display->key_stat.d_press = false;
        printf("D released\n");

    }
    if (key == XK_Left)
    {
        display->key_stat.left_press = false;
        printf("Left released\n");

    }
    if (key == XK_Right)
    {
        display->key_stat.right_press = false;
        printf("Right released\n");

    }
    return (0);
}

int	there_is_no_wall(t_display *display, int op, bool is_float)
{
	t_point tmp;

	if (!is_float)
	{
		tmp.x = display->player.pixels.x + display->player.delta_x * op;
		tmp.y = display->player.pixels.y + display->player.delta_y * op;
		tmp = pixel_to_bloc(tmp, display);
	}
	else
	{
		tmp.x = display->player.pixels.x + roundf(display->player.perp_x) * op;
		tmp.y = display->player.pixels.y + roundf(display->player.perp_y) * op;
		tmp = pixel_to_bloc(tmp, display);
	}
	if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
	{
		return (1);
	}
	return (0);
}

int game_engine(t_display *display)
{
    if (display->key_stat.w_press)
	{
		if (there_is_no_wall(display, 1, false))
		{
			player_move (display, 1, false);
		}
		clean_rendering(display);
	}
	if (display->key_stat.s_press)
	{
		if (there_is_no_wall(display, -1, false))
		{
			player_move (display, -1, false);
		}
		clean_rendering(display);
	}
	if (display->key_stat.a_press)
	{
		if (there_is_no_wall(display, -1, true))
		{
			player_move(display, -1, true);
		}
		clean_rendering(display);
	}
	else if (display->key_stat.d_press)
	{
		if (there_is_no_wall(display, 1, true))
		{
			player_move(display, 1, true);
		}
		clean_rendering(display);
	}
	if (display->key_stat.left_press)
	{
		orientation_player(display, -1);
		clean_rendering(display);
	}
	if (display->key_stat.right_press)
	{
		orientation_player(display, 1);
		clean_rendering(display);
	}
    return (0);
}
