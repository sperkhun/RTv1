#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/28 17:40:56 by sperkhun          #+#    #+#              #
#    Updated: 2018/02/28 17:40:57 by sperkhun         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RTv1

FLAGS = -Wall -Wextra -Werror

SRC = main.c draw.c intersection.c lighting.c traceray.c read_scene.c read_objects.c mlx.c

OBJ = $(SRC:.c=.o)

LIBFT = -L ./libft/ -lft

LIBMLX = -L /usr/local/lib/ -lmlx  -framework OpenGL -framework AppKit

INCL = -I ./libft/includes/ -I /usr/local/include

all: $(NAME)

%.o: %.c rtv1.h
	@gcc $(FLAGS) -c $< -o $@ $(INCL)

$(NAME): $(OBJ)
	@make -C ./libft/
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBMLX) $(LIBFT)
	@echo Creating $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@make -C ./libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all