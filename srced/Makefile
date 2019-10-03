NAME = editor
CC = clang
FILES = main \
	ed_add_protection \
	ed_bmp_reader \
	ed_init_structures \
	ed_init_editor \
	ed_init_texture \
	ed_init_assets \
	ed_draw \
	ed_draw_assets \
	ed_draw_string \
	ed_conversion \
	ed_pixel \
	ed_editor \
	ed_editor_functions \
	ed_editor_sector \
	ed_editor_wall \
	ed_editor_assets_handler \
	ed_editor_assets_handler2 \
	ed_list_manager_monster \
	ed_list_manager_assets \
	ed_event \
	ed_event_keyboard \
	ed_event_functions \
	ed_event_mouse_button \
	ed_event_functions2 \
	ed_event_assets_options \
	ed_event_sector_options \
	ed_interface \
	ed_interface_functions \
	ed_interface_print_values \
	ed_interface_map_list \
	ed_interface_select_map \
	ed_interface_properties \
	ed_interface_properties2 \
	ed_utils \
	ed_door_toggle \
	ed_detect_wall \
	ed_detect_assets \
	ed_read_map \
	ed_read_map_assets \
	ed_read_map_fix \
	ed_save_file \
	ed_fix_data_to_save \
	ed_save_monster \
	ed_save_weapons \
	ed_save_posters \
	ed_save_sound \
	ed_save_assets \
	ed_get_monster_files \
	ed_get_animation_files \
	ed_get_weapon_list \

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
				-F../frameworks/
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
