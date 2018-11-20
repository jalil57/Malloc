# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:47 by jtaibi            #+#    #+#              #
#    Updated: 2018/11/20 18:05:16 by jtaibi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

LIB = libft/libft.a

SRC = ./srcs/ft_malloc.c\
		./srcs/ft_free.c\
		./srcs/ft_realloc.c\
		./srcs/ft_malloc_debug.c

INCLUDES = ./includes/

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIB) -I $(INCLUDES) -o $(NAME);

%.o: %.c
	gcc $(FLAGS) -I $(INCLUDES) -o $@ -c $^

re: fclean all

clean:
	/bin/rm -Rf $(OBJ)

fclean: clean
	/bin/rm -Rf $(NAME)
