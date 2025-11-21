/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:18:18 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/21 15:43:00 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include <math.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
#include <stdbool.h>


#ifndef M_PI
# define M_PI 3.14159265358979 
#endif

#ifndef SPEED
# define  SPEED 5
#endif

#ifndef TETA
#define TETA M_PI/12
#endif

#ifndef SIZE_IMG
 #define SIZE_IMG 16
#endif

#ifndef FOV
 #define FOV M_PI/3
#endif

#ifndef SCRN_WIDTH
 #define SCRN_WIDTH 512
#endif

#ifndef SCRN_HEIGHT
 #define SCRN_HEIGHT 512
#endif

#ifndef WALL_UNIT
 #define WALL_UNIT 600
#endif

#ifndef MAX_DISTANCE
 #define MAX_DISTANCE 500
#endif

#ifndef NORTH
 #define NORTH 0
#endif

#ifndef SOUTH
 #define SOUTH 1
#endif

#ifndef EAST
 #define EAST 2
#endif

#ifndef WEST
 #define WEST 3
#endif

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
}	t_img;

typedef struct s_img_texture
{
    void        *img_ptr;
    char        *data;
    int         width;
    int         height;
    int         bpp;
    int         line_len;
    int         endian;
}   t_img_texture;

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

typedef struct s_shift
{
	int sreen_height;
	int	screen_width;
	int	size_img;
}t_shift;


typedef struct s_move
{
	bool	w_press;
	bool	a_press;
	bool	s_press;
	bool	d_press;
	bool	left_press;
	bool	right_press;
}t_move;

typedef struct s_hit
{
	float distance;
	t_point collision;
	int wall_direction;
}	t_hit;

typedef struct s_tex
{
	void	*wall_img;
	void	*floor_img;
	char 	*north;
	char 	*south;
	char 	*east;
	char 	*west;
	t_img_texture t_north;
	t_img_texture t_south;
	t_img_texture t_east;
	t_img_texture t_west;
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
	t_point	blocs;
	t_point pixels;

	float	delta_x;
	float	delta_y;
	
	float	perp_x;
	float	perp_y;
	
	float	angle;
	float	dir;
	float	rl_angle;

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
	t_mlx			mlx2;
	t_player		player;
	t_line			*head;
	t_point			begin;
	t_point			end;
	t_shift			shifter;
	t_img			all;
	t_img			rays;
	t_move			key_stat;
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


void	rad_to_deg(double rad);
void	render_all(t_display *display);
void	orientation_player(t_display * display, int operation);




void	cast_ray(t_point begin,t_display *display, int d);
int 	float_abs(float number);


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
int 	releasing_key(int key, void *param);

t_hit		draw_line_2(t_display *display, float beta);

void	free_texture(t_display *texture);
void	free_split(char **split);
int		quit_win(t_display *mlx);
int 	key_hook(int key, void *param);
long long	ft_atoll(const char *ptr);
int	get_rgb(t_rgb *rgb, char *str_rgb);
int		closed_error(char	**map);
int	is_player(char c);
int player_in_str(char *str);

void	img_initialization(t_display *display);
void	mini_map(t_display *display, char **map);
void	draw_line(t_display *display);
void	rotate_player(t_display *display, float angle);

t_point calculate_end(t_point begin, float angle, int max_distance);
t_point	pixel_to_bloc(t_point pixel, t_display *display);

void	ray_fov(t_point begin,t_display *display, int d);
float		to_wall(t_display *display, t_point collision, float beta);
void	draw_textured_line(t_line *line, t_hit hit, int line_size, t_display *display);
int		shifter(int	number);
void	img_pix_put(t_img *img, int x, int y, int color);
void    clear_img(t_display *display);
void	clear_rays(t_display *display);
int    	game_engine(t_display *display);
void	player_move (t_display *display, int opx, int opy, double angle);
void    load_textures(t_display *display);
int     sample_texture(t_img_texture *img_tex, float u, float v);
void	aff_floor_and_ceiling(t_display *display);

int get_wall_direction(t_point collision, t_point player_pos);
#endif