/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:41:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/22 14:28:34 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	clean_rendering(t_display *display)
{
	//clear_img(display);
   	clear_rays(display);
	mlx_clear_window(display->mlx.mlx_ptr, display->mlx.win_ptr);
	render_all(display);
}

int releasing_key(int key, void *param)
{
    t_display  *display;

    display = (t_display *)param;
    (void)display;
    if (key == XK_W || key == XK_w)
        display->key_stat.w_press = false;
    if (key == XK_A || key == XK_a)
        display->key_stat.a_press = false;
    if (key == XK_S || key == XK_s)
        display->key_stat.s_press = false;
    if (key == XK_D || key == XK_d)
        display->key_stat.d_press = false;
    if (key == XK_Left)
        display->key_stat.left_press = false;
    if (key == XK_Right)
        display->key_stat.right_press = false;
    return (0);
}

static int	is_wall_at(t_display *display, int px, int py)
{
	t_point	bloc;

	bloc.x = px >> display->shifter.size_img;
	bloc.y = py >> display->shifter.size_img;
	if (bloc.y < 0 || bloc.y >= display->texture.map_height)
		return (1);
	if (bloc.x < 0 || bloc.x >= display->texture.map_width)
		return (1);
	if (!display->map[bloc.y][bloc.x] || display->map[bloc.y][bloc.x] == '1')
		return (1);
	return (0);
}

int	there_is_no_wall(t_display *display, int op, bool is_float)
{
	int	new_x;
	int	new_y;

	if (!is_float)
	{
		new_x = display->player.pixels.x + roundf(display->player.delta_x) * op;
		new_y = display->player.pixels.y + roundf(display->player.delta_y) * op;
	}
	else
	{
		new_x = display->player.pixels.x + roundf(display->player.perp_x) * op;
		new_y = display->player.pixels.y + roundf(display->player.perp_y) * op;
	}
	if (is_wall_at(display, new_x - COLLISION_MARGIN, new_y - COLLISION_MARGIN))
		return (0);
	if (is_wall_at(display, new_x + COLLISION_MARGIN, new_y - COLLISION_MARGIN))
		return (0);
	if (is_wall_at(display, new_x - COLLISION_MARGIN, new_y + COLLISION_MARGIN))
		return (0);
	if (is_wall_at(display, new_x + COLLISION_MARGIN, new_y + COLLISION_MARGIN))
		return (0);
	return (1);
}
void	moving(t_display *display, int op, bool is_float)
{
	if (there_is_no_wall(display, op, is_float))
		player_move (display, op, is_float);
	clean_rendering(display);
}

int game_engine(t_display *display)
{
    if (display->key_stat.w_press)
		moving(display, 1, false);
	else if (display->key_stat.s_press)
		moving(display, -1, false);
	if (display->key_stat.a_press)
		moving(display, -1, true);
	else if (display->key_stat.d_press)
		moving(display, 1, true);
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
		//clean_rendering(display);

    return (0);
}
