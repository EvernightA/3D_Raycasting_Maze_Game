/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:58:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/20 13:08:42 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"

#ifndef SIZE_IMG
 #define SIZE_IMG 16
#endif

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
}	t_img;

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

typedef struct s_rgb
{
	int red;
	int green;
	int blue;
}	t_rgb;


typedef struct s_tex
{
	void	*wall_img;
	void	*floor_img;
	char 	*north;
	char 	*south;
	char 	*east;
	char 	*west;
	char	*c_rgb;
	char	*f_rgb;
	t_rgb	ceiling_rgb;
	t_rgb	floor_rgb;
	// char	**map;
	char	**dup_map;
	int		map_height;
} t_tex;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct s_player
{
	int 	x_blocs;
	int 	x_pixel;
	int 	y_blocs;
	int 	y_pixel;
	int 	fov;
	t_point	direction;
	char 	orientation;
}
				t_player;

typedef struct s_display
{
	char			**map;
	t_tex			texture;
	t_mlx			mlx;
	t_player		player;
}				t_display;

char	**dup_mat(int height, char **map);
size_t	find_len_max(char **map);
int 	map_invalid(int i, int j, int k, char **map);
char	*ft_strdup_x(char *s, int len);


int		is_player(char c);
int		is_unknown(char c);
int		player_error(int count);
int		player_in_str(char *str);
int		matrix_height(char **matrix);





void	print_map(char **map);
int		count_map_lines(int fd);
char	**get_map(char *gnl, int fd, int map_height);
void	get_elements(int fd, t_display *texture, int map_height);
void	store_texture(char *str, t_display *texture);
t_line	*bresenham_line(t_point *begin, t_point *end);
int		ft_linesize(t_line *line);
void	ft_lineadd_back(t_line **line, t_line *new);
t_line	*ft_linenew(t_point content);
void	ft_linefree(t_line **line);
void	print_list(t_line *head);
int		error_handling(t_display *texture);
int 	texture_error(t_display *texture);


void	free_texture(t_display *texture);
void	free_split(char **split);
int		quit_win(t_display *mlx);
int 	key_hook(int key, void *param);
long long	atoll(const char *ptr);
int	get_rgb(t_rgb *rgb, char *str_rgb);
int		closed_error(char	**map);
int	is_player(char c);
int player_in_str(char *str);

void	img_initialization(t_display *display);
void	mini_map(t_display *display, char **map);



#endif