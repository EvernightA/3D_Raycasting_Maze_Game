CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = cub3D 

MLXFLAGS =  -Lminilibx-linux ./minilibx-linux/libmlx_Linux.a ./libft/libft.a -lX11 -lXext

LIBFT = ./libft/libft.a

SRCS_DIR = ./srcs/

OBJ_DIR = ./objs/

SRCS =  $(SRCS_DIR)main.c \
	    $(SRCS_DIR)parse.c \
	    $(SRCS_DIR)map_parsing.c \
		$(SRCS_DIR)bresenham.c\
		$(SRCS_DIR)line_utils.c\
		$(SRCS_DIR)frees.c \
		$(SRCS_DIR)mlx_utils.c

OBJ = $(SRCS:$(SRCS_DIR)%.c=%.o)

MLX = ./minilibx-linux/libmlx_Linux.a

MINILIBX = ./minilibx-linux/

all : $(NAME)

$(LIBFT):
	make -C ./libft

$(MLX) :
	make -C $(MINILIBX)

$(OBJ) : $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME);

clean:
	make clean -C $(MINILIBX)
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re