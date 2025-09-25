/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:58:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 09:55:19 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	dp;
}t_point;

typedef struct  s_line
{
	t_point dot;
	struct	s_line *next;
} t_line;



typedef struct s_tex
{
	int		completed;
	char 	*north;
	char 	*south;
	char 	*east;
	char 	*west;
	char	*c_rgb;
	char	*f_rgb;
	char	**map;

} t_tex;



int		count_map_lines(int fd);
char	**get_map(char *gnl, int fd, int map_height);
void	get_elements(int fd, t_tex *texture, int map_height);
void	store_texture(char *str, t_tex *texture);
t_point	bresenham_line(t_point *begin, t_point *end);

#endif