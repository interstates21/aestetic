# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/18 21:20:37 by vslutiak          #+#    #+#              #
#    Updated: 2019/07/18 21:32:01 by vslutiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_DIR = ./srcs/
OBJ_DIR = ./
INC_DIR = ./includes/
LIB_DIR = ./libft/
HEADERS = $(INC_DIR)wolf.h

SRC = dd.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC = gcc  -I ./LIB/SDL2.framework/Versions/A/Headers -F ./LIB/ \
 -I ./LIB/SDL2_mixer.framework/Versions/A/Headers -F ./LIB/ \
 -I ./LIB/SDL2_image.framework/Versions/A/Headers -F ./LIB/

FLAGS = -framework SDL2 -framework SDL2_mixer -framework SDL2_image

#LIBFT_DIR = $(LIB_DIR)
#LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(OBJ)
	#@make -C $(LIBFT_DIR)
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: %.c $(HEADERS) Makefile
	$(CC) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -f $(OBJ)
	#@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	#@make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SRC_DIR)