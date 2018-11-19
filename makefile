# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaibi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:47 by jtaibi            #+#    #+#              #
#    Updated: 2018/04/01 19:37:39 by jtaibi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

LIB = libft/libft.a

SRC = ft_malloc.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $^

re: fclean all

clean:
	/bin/rm -Rf $(OBJ)

fclean: clean
	/bin/rm -Rf $(NAME)
