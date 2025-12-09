/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:32 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/09 16:14:20 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_texture(t_img_texture **texture_to_display, t_hit hit, t_display *display)
{
	(void)texture_to_display;
	if (hit.wall_direction == NORTH)
		*texture_to_display = &display->texture.t_north;
	else if (hit.wall_direction == SOUTH)
		*texture_to_display = &display->texture.t_south;
	else if (hit.wall_direction == EAST)
		*texture_to_display = &display->texture.t_east;
	else
		*texture_to_display = &display->texture.t_west;
}

void    draw_textured_line(t_line *line, t_hit hit, int line_size, t_display *display)
{
        t_line *tmp;
		float uv_x;
		float uv_y;
		t_img_texture *texture_to_display;
		int texture_color;
		int count;

        tmp = line;
		count = 0;
		texture_to_display = &display->texture.t_north;;
		set_texture(&texture_to_display, hit, display);
        while (tmp)
        {
			if (hit.wall_direction == NORTH || hit.wall_direction == SOUTH)
				uv_x = fmodf(hit.collision.f_x, SIZE_IMG) / SIZE_IMG;
			else
				uv_x = fmodf(hit.collision.f_y, SIZE_IMG) / SIZE_IMG;
            uv_y = (float)count / line_size;
            texture_color = sample_texture(texture_to_display, uv_x, uv_y);
            img_pix_put(&display->all, tmp->dot.x, tmp->dot.y, texture_color);
			count ++;
            tmp = tmp -> next;
        }
}

void		draw_line(t_display *display)
{
	t_line *tmp;
	t_point tmp_bloc;

	tmp = display->head;
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (display->map[tmp_bloc.y][tmp_bloc.x] == '0' || is_player(display->map[tmp_bloc.y][tmp_bloc.x]))
			mlx_pixel_put(display->mlx.mlx_ptr, display->mlx.win_ptr,tmp->dot.x,tmp->dot.y, 0xFF000);
		else
		{
			break;
		}
		tmp = tmp -> next;
	}
}

void	east_case(float normalised_x, t_hit *hit, t_point bloc, t_display *display)
{
	int dx;
	int dy;
	int wall_above;
	int wall_below;

	dx = (int)(hit->collision.f_x / 16) - display->player.blocs. x;
	dy = (int)(hit->collision.f_y / 16) - display->player.blocs.y;

	if (dx < 0 && dy > 0 && hit->wall_direction == NORTH)
	{
		if (display->map[bloc. y][bloc. x + 1] != '1')
		{
			wall_above = (display->map[bloc.y - 1][bloc. x] == '1');
			wall_below = (display->map[bloc.y + 1][bloc.x] == '1');

			// True edge (walls both sides) - correct aggressively
			if (wall_above && wall_below && normalised_x >= 15.0f)
				hit->wall_direction = EAST;
			// Partial edge (wall on one side) - moderate correction
			else if ((wall_above || wall_below) && normalised_x >= 15.0f)
				hit->wall_direction = EAST;
			// Isolated corners - very strict
			else if (normalised_x >= 15.0f)
				hit->wall_direction = EAST;
		}
	}

	if (dx < 0 && dy < 0 && hit->wall_direction == SOUTH)
	{
		if (display->map[bloc. y][bloc.x + 1] != '1')
		{
			wall_above = (display->map[bloc.y - 1][bloc.x] == '1');
			wall_below = (display->map[bloc.y + 1][bloc.x] == '1');

			// True edge (walls both sides) - correct aggressively
			if (wall_above && wall_below && normalised_x >= 15.0f)
				hit->wall_direction = EAST;
			// Partial edge (wall on one side) - moderate correction
			else if ((wall_above || wall_below) && normalised_x >= 15.0f)
				hit->wall_direction = EAST;
			// Isolated corners - very strict
			else if (normalised_x >= 15.0f)
				hit->wall_direction = EAST;
		}
	}
}

void	west_case(float normalised_x, t_hit *hit, t_point bloc, t_display *display)
{
	int dx;
	int dy;
	int wall_above;
	int wall_below;

	dx = (int)(hit->collision.f_x / 16) - display->player.blocs.x;
	dy = (int)(hit->collision.f_y / 16) - display->player.blocs.y;

	if (dx > 0 && dy > 0 && hit->wall_direction == NORTH)
	{
		if (display->map[bloc. y][bloc.x - 1] != '1')
		{
			wall_above = (display->map[bloc.y - 1][bloc.x] == '1');
			wall_below = (display->map[bloc.y + 1][bloc.x] == '1');

			// True edge (walls both sides) - correct aggressively
			if (wall_above && wall_below && normalised_x <= 1.0f)
				hit->wall_direction = WEST;
			// Partial edge (wall on one side) - moderate correction
			else if ((wall_above || wall_below) && normalised_x <= 1.0f)
				hit->wall_direction = WEST;
			// Isolated corners - very strict
			else if (normalised_x <= 1.0f)
				hit->wall_direction = WEST;
		}
	}

	if (dx > 0 && dy < 0 && hit->wall_direction == SOUTH)
	{
		if (display->map[bloc. y][bloc.x - 1] != '1')
		{
			wall_above = (display->map[bloc.y - 1][bloc.x] == '1');
			wall_below = (display->map[bloc.y + 1][bloc.x] == '1');

			// True edge (walls both sides) - correct aggressively
			if (wall_above && wall_below && normalised_x <= 1.0f)
				hit->wall_direction = WEST;
			// Partial edge (wall on one side) - moderate correction
			else if ((wall_above || wall_below) && normalised_x <= 1.0f)
				hit->wall_direction = WEST;
			// Isolated corners - very strict
			else if (normalised_x <= 1.0f)
				hit->wall_direction = WEST;
		}
	}
}

void	direct_fix(float normalised_x, t_hit *hit, t_point bloc, t_display *display)
{
	char prev_wall_char;
	char next_wall_char;
	int dx;
	int dy;

	dx = (int)(hit->collision.f_x / 16) - display->player.blocs.x;
    dy = (int)(hit->collision.f_y / 16) - display->player.blocs.y;
	prev_wall_char = display->map[bloc.y - 1][bloc.x];
	next_wall_char = display->map[bloc.y + 1][bloc.x];
	if (display->map[bloc.y][bloc.x] == prev_wall_char
	&& prev_wall_char == next_wall_char)
	{
		if ((dx < 0 && dy < 0) || (dx < 0 && dy > 0))
			hit->wall_direction = EAST;
		else
			hit->wall_direction = WEST;
	}
	else
	{
		normalised_x = fmodf(hit->collision.f_x, 16);
		east_case(normalised_x, hit, bloc, display);
		west_case(normalised_x, hit, bloc, display);
	}
	printf("wall_dir = %d, dx = %d, dy = %d, hitwc = %f, dpy+1 = '%c', dpy-1 = '%c', dpx+1='%c', dpx-1 = '%c'\n", hit->wall_direction, dx, dy, normalised_x, display->map[bloc.y + 1][bloc.x], display->map[bloc.y - 1][bloc.x], display->map[bloc.y][bloc.x + 1], display->map[bloc.y][bloc.x - 1]);
}

int	direction_fix(t_display *display, t_hit *hit, t_point bloc)
{
	float normalised_x = 0;

	if (hit->wall_direction == NORTH || hit->wall_direction == SOUTH)
	{
		bloc = pixel_to_bloc(hit->collision, display);
		if (bloc.y <= 0 || bloc.y >= display->texture.map_height - 1
			|| !(display->map[bloc.y][bloc.x]))
			return (1);
		direct_fix(normalised_x, hit, bloc, display);
	}
	return (0);
}
void	init_hit(t_hit *hit)
{
	(void)hit;
	hit->distance = 0;
	hit->collision.x = 0;
	hit->collision.y = 0;
	hit->collision.f_x = 0;
	hit->collision.f_y = 0;
	// before = NULL;
}

void	wall_assign(t_hit *hit, t_line *tmp, t_display *display, float beta)
{
	hit->collision = tmp->dot;
	hit->distance = to_wall(display, tmp->dot, beta);
	hit->wall_direction = get_wall_direction(hit->collision, display->player.blocs);
}

int	go_to_next_node(t_line **tmp, t_line **before, t_hit *hit, t_display *display)
{
	if ((*tmp)->next == NULL)
	{
		*before = *tmp;
		wall_assign(hit, *before, display, display->beta);
		return (1);
	}
	*tmp = (*tmp)->next;
	return (0);
}

int is_walkable(t_display *display, t_point tmp_bloc)
{
	return (display->map[tmp_bloc.y][tmp_bloc.x] == '0'
			|| is_player(display->map[tmp_bloc.y][tmp_bloc.x]));
}

t_hit		draw_line_2(t_display *display, float beta)
{
	t_line *tmp;
	t_line	*before;
	t_point tmp_bloc;
	t_hit 	hit;
	t_point bloc;

	tmp = display->head;
	before = NULL;
	init_hit(&hit);
	while (tmp)
	{
		tmp_bloc = pixel_to_bloc(tmp->dot, display);
		if (is_walkable(display, tmp_bloc))
		{
			//img_pix_put(&display->rays, tmp->dot.x, tmp->dot.y, 0x00F0);
		}
		else
		{
			wall_assign(&hit, tmp, display, beta);
			direction_fix(display, &hit, bloc);
			break ;
		}
		display->beta = beta;
		if (go_to_next_node(&tmp, &before, &hit, display))
			break ;
	}
	return (hit);
}
