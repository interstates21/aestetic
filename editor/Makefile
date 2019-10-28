
NAME = dm_editor
CC = clang
FILES = bmp_reader \
                    draw_info \
                    char_selector \
                    font \
					r_helpers \
					r_sdl \
					r_sdl2 \
					r_push \
					loop_creation \
					r_controls \
					reopen \
                    init_sector \
                    init_monsters \
                    init_sprites \
                    init_textures \
                    load_anims \
                    main \
					loop \
                    savior \
					r_line \
					r_vector \
					r_mouse_controller \
					r_bold_line \
					r_selectors \
					r_texture_picker \
					r_circle \
                    save_mnst_tex \
                    load_weapon \
                    save_monsters \
                    save_sectors \
                    save_tex \
                    tex_finder \
                    save_weapon \
					r_pickers
LIBFT_DIR = ../libft/
SRC = $(addsuffix .c, $(FILES))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))
SDL_CFLAGS = $(shell sdl2-config --cflags)
SPEED = -O3
FLAGSTMP = -Wall -Wextra -Werror
MATH = -lm
HEADERS = -I../includes -I../libft

OS = $(shell uname)
ifeq ($(OS), Linux)
CGFLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
else
CGFLAGS = -framework OpenGL -framework AppKit
INCLUDES	=	-I../frameworks/SDL2.framework/Versions/A/Headers \
				-I../frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I../frameworks/SDL2_image.framework/Versions/A/Headers \
				-I../frameworks/SDL2_mixer.framework/Headers \
				-F../frameworks
FRAMEWORKS	=	-F../frameworks \
				-rpath ../frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer 
endif

all: $(NAME)

.PHONY: all clean
.NOTPARALLEL: all $(NAME) clean fclean re

$(NAME): ../libft/libft.a $(OBJ)
	@echo "\033[36mLinking...\033[0m"
	@$(CC) -o $(NAME) $(FLAGS) $(SPEED) $(OBJ) $(CGFLAGS) ${MATH} $(FRAMEWORKS) ../libft/libft.a
	@echo "\033[32m[ ✔ ] Binary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
../libft/libft.a:
	@make --no-print-directory -j3 -C $(LIBFT_DIR)
obj/%.o: %.c
	@$(CC) -o $@ $(FLAGS) $(SPEED) $(HEADERS) $(INCLUDES) -c $^
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
