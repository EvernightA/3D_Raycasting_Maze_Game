/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:58:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 11:51:55 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"

# define K_ESC 65307

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

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct s_display
{
	char			**map;
	t_tex			texture;
	t_mlx			mlx;
}				t_display;

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
void	free_texture(t_tex *texture);
void	free_split(char **split);
int		quit_win(t_mlx *mlx);
int 	key_hook(int key, void *param);


#endif