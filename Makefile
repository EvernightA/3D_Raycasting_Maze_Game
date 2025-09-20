CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D 

MLXFLAGS =  -Lminilibx-linux ./minilibx-linux/libmlx_Linux.a -lX11 -lXext

SRCS = ./srcs/main.c \

OBJ = $(SRCS:%.c=%.o)

MLX = ./minilibx-linux/libmlx_Linux.a

all : $(NAME)

$(LIBFT):
	make -C ./libft

$(MLX) :
	make -C $(MINILIBX)

$(OBJ) : $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ) $(LIBFT) $(MLX) 
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	make clean -C $(MINILIBX)
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re