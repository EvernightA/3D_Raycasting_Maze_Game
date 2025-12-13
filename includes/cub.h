/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:18:18 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/12/13 14:50:54 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef LARGE_DIST
#  define LARGE_DIST 1e30f
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979
# endif

# ifndef SPEED
#  define SPEED 1.5
# endif

# ifndef TETA
#  define TETA 0.034906585
# endif

# ifndef SIZE_IMG
#  define SIZE_IMG 16
# endif

# ifndef FOV
#  define FOV 1.0472
# endif

#ifndef SCRN_WIDTH
 #define SCRN_WIDTH 800
#endif

#ifndef SCRN_HEIGHT
 #define SCRN_HEIGHT 600
#endif

# ifndef MAX_DISTANCE
#  define MAX_DISTANCE 600
# endif

# ifndef NORTH
#  define NORTH 0
# endif

# ifndef SOUTH
#  define SOUTH 1
# endif

# ifndef EAST
#  define EAST 2
# endif

# ifndef WEST
#  define WEST 3
# endif

typedef struct s_img
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_img_texture
{
	void			*img_ptr;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img_texture;

typedef struct s_point
{
	int				x;
	int				y;
	float			f_x;
	float			f_y;
	int				dp;
}					t_point;

typedef struct s_line
{
	t_point			dot;
	struct s_line	*next;
}					t_line;

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct s_shift
{
	int				sreen_height;
	int				screen_width;
	int				size_img;
}					t_shift;

typedef struct s_bres
{
	t_point			current;
	t_line			*head;
	t_line			*new_node;
	t_line			*tail;
	int				delta_x;
	int				delta_y;
	int				x_step;
	int				y_step;
	int				err;
	int				dp;
}					t_bres;

typedef struct s_dda
{
	float			dx;
	float			dy;
	float			steps;
	float			x_inc;
	float			y_inc;
	float			x;
	float			y;
	int				i;
	t_point			current;
	t_line			*head;
	t_line			*new_node;
	t_line			*tail;
}					t_dda;

typedef struct s_move
{
	bool			w_press;
	bool			a_press;
	bool			s_press;
	bool			d_press;
	bool			left_press;
	bool			right_press;
}					t_move;

typedef struct s_hit
{
	float			distance;
	int				collision;
	int				wall_direction;
}					t_hit;

typedef struct s_tex
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	t_img_texture	t_north;
	t_img_texture	t_south;
	t_img_texture	t_east;
	t_img_texture	t_west;
	char			*c_rgb;
	char			*f_rgb;
	t_rgb			ceiling_rgb;
	t_rgb			floor_rgb;
	char			**dup_map;
	int				map_height;
	int				map_width;
}					t_tex;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct s_player
{
	t_point			blocs;
	t_point			pixels;

	float			delta_x;
	float			delta_y;

	float			perp_x;
	float			perp_y;

	float			angle;
	float			dir;
	float			rl_angle;

	int				fov;
	t_point			direction;
	char			orientation;
}					t_player;

typedef struct s_ray
{
	float			dir_x;
	float			dir_y;
	int				map_x;
	int				map_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			side_dist_x;
	float			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	float			perp_wall_dist;
	float			wall_x;
	int				wall_dir;
	float			angle_offset;
}					t_ray;


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
	float			beta;
	t_ray			ray;
}					t_display;

typedef struct s_tex_utils
{
	t_line			*tmp;
	t_img_texture	*texture_to_display;
	int				count;
}					t_tex_utils;

char				**dup_mat(t_display *display, int height, char **map);
int					ft_abs(int n);
size_t				find_len_max(char **map);
int					map_invalid(int i, int j, int k, char **map);
char				*ft_strdup_x(char *s, int len);

void				filter_texture(t_display *display);

int					is_player(char c);
int					is_unknown(char c);
int					player_error(int count, t_display *display);
int					player_in_str(char *str);
int					matrix_height(char **matrix);

void				render_all(t_display *display);
void				orientation_player(t_display *display, int operation);

void				cast_ray(t_display *display);
int					float_abs(float number);
int					get_map_height(t_display *display, int *map_height,
						char *file);
int					count_map_lines(int fd);
char				**get_map(char *gnl, int fd, int map_height);
void				get_elements(int fd, t_display *texture, int map_height);
void				store_texture(char *str, t_display *texture);
t_line				*bresenham_line(t_point *begin, t_point *end);
t_line				*dda_line(t_display *display);
int					ft_linesize(t_line *line);
void				ft_lineadd_back(t_line **line, t_line *new);
t_line				*ft_linenew(t_point content);
void				ft_linefree(t_line **line);
void				print_list(t_line *head);
int					error_handling(t_display *texture);
int					texture_error(t_display *texture);
int					releasing_key(int key, void *param);

t_hit				draw_line(t_display *display, float beta);

void				free_texture(t_display *texture);
void				free_split(char **split);
int					quit_win(t_display *mlx);
int					key_hook(int key, void *param);
long long			ft_atoll(const char *ptr);
int					get_rgb(t_rgb *rgb, char *str_rgb);
int					closed_error(char **map);
int					is_player(char c);
int					player_in_str(char *str);
int					parsing(int *map_height, char *file, t_display *display);

void				img_initialization(t_display *display);
void				rotate_player(t_display *display, float angle);
t_point				pixel_to_bloc(t_point pixel, t_display *display);
void				draw_textured_line(t_line *line, t_hit hit, int line_size,
						t_display *display);
int					shifter(int number);
void				img_pix_put(t_img *img, int x, int y, int color);
int					game_engine(t_display *display);
void				player_move(t_display *display, int op, bool is_float);

void				load_textures(t_display *display);
int					sample_texture(t_img_texture *img_tex, int tex_x, int tex_y);
void				aff_floor_and_ceiling(t_display *display);
void				free_tex_map(t_display *display);
void				init_player_pos(t_display *display, int i, int j);
void				init_it(t_display *display);
void				init_direction(t_display *display, int x_dir, int y_dir,
						float angle);
int					input_error(int argc, char **argv);
void				calculus_dir(t_display *display);
void				orientation_init(t_display *display, int i, int j);
int					something_is_wrong(t_display *display, char **argv,
						int argc, int *map_height);
int					successive_commas(int *i, char *og_rgb);
int					rgb_error(char **split_rgb, char *str_rgb);
int					overflowing_values(char **split_rgb);
int					non_numeric_values(char **split_rgb);
int					not_enough_values(char **split_rgb);
void				init_xpm_image(t_display *display);
void				load_textures(t_display *display);
void				init_ray_direction(t_display *display, float angle);
void				init_step_and_side_dist(t_display *display);
#endif
