/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:41:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/15 17:14:09 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

int game_engine(t_display *display)
{
    t_point tmp;
    
    // printf ("YOU ARE HERE\n");
    // while (1)
    // {
    clear_img(display);
    clear_rays(display);

    /*calculating the time to calculate the distance*/
	display->timer.current_time = get_time() - display->timer.start_time;
	display->timer.delta_time = (display->timer.current_time - display->timer.last_time) / 1000; // for secs
	display->timer.last_time = display->timer.current_time;
	/****************************************************/
	/*DISTANCE = SPEED * delta_time */
	if (display->key_stat.w_press)
	{
		// tmp is too see if next is a wall
		// display->key_stat.w_press = true;
			// display->timer
			tmp.x = display->player.pixels.x + display->player.delta_x;
			tmp.y = display->player.pixels.y + display->player.delta_y;
			tmp = pixel_to_bloc(tmp, display);
			if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
			{
				player_move (display, 1, 1, display->player.angle);
			}
		// render_all(display);
	}
	if (display->key_stat.s_press)
	{
		// tmp is too see if next is a wall
		// display->key_stat.s_press = true;
		tmp.x = display->player.pixels.x - display->player.delta_x;
		tmp.y = display->player.pixels.y - display->player.delta_y;
		tmp = pixel_to_bloc(tmp, display);
		if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			player_move (display, -1, -1, display->player.angle);
		}
		// render_all(display);
    
	}
	if (display->key_stat.a_press)
		// tmp is too see if next is a wall
	{
		// display->key_stat.a_press = true;
		tmp.x = display->player.pixels.x - display->player.perp_x;
		tmp.y = display->player.pixels.y - display->player.perp_y;
		// printf("cos = %f, sin = %f\n", cos(display->player.angle), sin(display->player.angle));
		tmp = pixel_to_bloc(tmp, display);
		if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			display->player.pixels.x = display->player.pixels.x - display->player.perp_x;
			display->player.pixels.y = display->player.pixels.y - display->player.perp_y;
			display->begin.y = display->player.pixels.y;
			display->begin.x = display->player.pixels.x;
			display->player.blocs = pixel_to_bloc(display->player.pixels, display);
			display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
		}
		// render_all(display);
	}
	if (display->key_stat.d_press)
	{
		// tmp is too see if next is a wall
		// display->key_stat.d_press = true;
		tmp.x = display->player.pixels.x + display->player.perp_x;
		tmp.y = display->player.pixels.y + display->player.perp_y;
		// printf("cos = %f, sin = %f\n", cos(display->player.angle), sin(display->player.angle));
		tmp = pixel_to_bloc(tmp, display);
		if (tmp.y < display->texture.map_height && display->map[tmp.y][tmp.x] && display->map[tmp.y][tmp.x] != '1')
		{
			// player_move(display, -1, -1, display->player.angle);
			display->player.pixels.x = display->player.pixels.x + display->player.perp_x;
			display->player.pixels.y = display->player.pixels.y + display->player.perp_y;
			display->begin.y = display->player.pixels.y;
			display->begin.x = display->player.pixels.x;
			display->player.blocs = pixel_to_bloc(display->player.pixels, display);
			display->map[display->player.blocs.y][display->player.blocs.x] = display->player.orientation;
		}
		// render_all(display);
	}
	if (display->key_stat.left_press)
	{
		// display->key_stat.left_press = true;
		orientation_player(display, -1);
		rad_to_deg(display->player.angle);
		// rad_to_deg(display->player.rl_angle);
		// render_all(display);
	}
	if (display->key_stat.right_press)
	{
		// display->key_stat.right_press = true;
		orientation_player(display, 1);
		rad_to_deg(display->player.angle);
		// rad_to_deg(display->player.angle);
	}
	render_all(display);
    // ft_putstr_fd("WUUUUUT\n", 1);
        // sleep(1);
    return (0);
       // }
}