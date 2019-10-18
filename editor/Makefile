# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 20:10:50 by akolomoi          #+#    #+#              #
#    Updated: 2019/10/18 20:10:51 by akolomoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dm_editor

FILES =	bmp_reader \
            init_monsters \
            init_sdl \
            init_sprites \
            init_textures \
            load_anims \
            main

LIBFT_DIR = ../libft/
SRC = $(addsuffix .c, $(FILES))
OBJ = $(addsuffix .o, $(FILES))
OBJ_LIST = OBJ

MATH = -lm
HEADERS = -I../includes -I../libft


CGFLAGS = -framework OpenGL -framework AppKit
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

all: $(NAME)

.PHONY: all clean
.NOTPARALLEL: all $(NAME) clean fclean re

$(NAME): libft/libft.a $(OBJ)
	@echo "\033[36mLinking...\033[0m"
	@gcc -o $(NAME) $(FLAGS) $(OBJ) $(CGFLAGS) ${MATH} $(FRAMEWORKS) ../libft/libft.a
	@echo "\033[32m[ ✔ ] Binary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
libft/libft.a:
	@make --no-print-directory -j3 -C $(LIBFT_DIR)
obj/%.o: src/%.c
	@gcc -o $@ $(FLAGS) $(HEADERS) $(INCLUDES) -c $^
	@echo "\033[37mCompilation of \033[97m$(notdir $<) \033[0m\033[37mdone. \033[0m"
clean:
	@rm -f $(OBJ)
	@make --no-print-directory -j3 -C ../libft/ clean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
fclean:
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@make --no-print-directory -j3 -C ../libft/ fclean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
	@echo "\033[31m[ ✔ ] Binary \033[1;31m$(NAME) \033[1;0m\033[31mremoved.\033[0m"
re: fclean all
