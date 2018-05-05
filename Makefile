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

SRC = main.c draw.c intersection.c lighting.c traceray.c read_scene.c read_objects.c sdl.c

OBJ = $(SRC:.c=.o)

LIBFT = -L ./libft/ -lft

LISDL = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_mixer

INCL = -I ./libft/includes/ -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LISDL) $(LIBFT)
	@echo Creating $(NAME)

%.o: %.c rtv1.h
	@gcc $(FLAGS) -c $< -o $@ $(INCL) -pthread

clean:
	@/bin/rm -f $(OBJ)
	@make -C ./libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft/ fclean
re: fclean all