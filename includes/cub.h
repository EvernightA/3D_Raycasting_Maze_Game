/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:58:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/24 14:55:36 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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

typedef struct s_point
{
	int	x;
	int	y;
	int	dp;
}t_point;

int		count_map_lines(int fd);
char	**get_map(char *gnl, int fd, int map_height);
void	get_elements(int fd, t_tex *texture, int map_height);
void	store_texture(char *str, t_tex *texture);

#endif