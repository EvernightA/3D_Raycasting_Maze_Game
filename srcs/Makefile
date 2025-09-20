CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = ../srcs/cub3D 

MLXFLAGS =  -Lminilibx-linux ../minilibx-linux/libmlx_Linux.a ../libft/libft.a -lX11 -lXext

LIBFT = ../libft/libft.a

SRCS = ../srcs/main.c \
	   ../srcs/parse.c

OBJ = $(SRCS:%.c=%.o)

MLX = ../minilibx-linux/libmlx_Linux.a

MINILIBX = ../minilibx-linux/

all : $(NAME)

$(LIBFT):
	make -C ../libft

$(MLX) :
	make -C $(MINILIBX)

$(OBJ) : $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ) $(LIBFT) $(MLX) 
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	make clean -C $(MINILIBX)
	make clean -C ../libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ../libft
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re