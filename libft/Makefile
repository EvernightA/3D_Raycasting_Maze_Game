# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 18:11:01 by fsamy-an          #+#    #+#              #
#    Updated: 2025/08/18 19:22:13 by fsamy-an         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c ft_count_number.c ft_print_memory.c ft_printf.c ft_putnbr_unsigned.c ft_string_len.c ft_hexadecimal.c ft_condition.c ft_putchar.c ft_putnbr.c ft_count_unsigned.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strrchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_memmove.c ft_split.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJ = $(BONUS:%.c=%.o)

OBJ = $(SRCS:%.c=%.o)

NAME = libft.a

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $(SRCS)
	@echo "Compiling libft functions into object files ..."

$(NAME) : $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@echo "Add object files to libft.a ..."

$(BONUS_OBJ) : $(BONUS)
	@$(CC) $(CFLAGS) -c $(BONUS)
	@echo "Compiling linked list functions into object files ..."

bonus : $(BONUS_OBJ) $(OBJ)
	@ar -rcs $(NAME) $(BONUS_OBJ)
	@echo "Adding linked list objects to libft.a ..."

clean :
	@rm -f $(OBJ) $(BONUS_OBJ)
	@echo "Removing object files in libft ..."

fclean : clean
	@rm -f $(NAME)
	@echo "Removing libft.a ..."

re : fclean all

.PHONY : all clean fclean bonus re