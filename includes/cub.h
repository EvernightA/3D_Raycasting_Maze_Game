/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:58:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 11:46:40 by fsamy-an         ###   ########.fr       */
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
t_line	*bresenham_line(t_point *begin, t_point *end);
int		ft_linesize(t_line *line);
void	ft_lineadd_back(t_line **line, t_line *new);
t_line	*ft_linenew(t_point content);
void	ft_linefree(t_line **line);
void	print_list(t_line *head);
int		error_handling(t_tex *texture);




#endif