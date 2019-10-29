NAME = doom_nukem
CC = clang
FILES = main \
		loading \
		next_sect_fix \
		atoi \
		interact_with_assets \
		d_asseting \
		d_asseting2 \
		d_ceil_floor \
		d_sky \
		d_huds \
		d_jetp_hud \
		d_ammo_hud \
		dr_monster \
		display_data \
		d_sprite \
		disp_sprite \
		d_wall \
		d_wall2 \
		d_proj \
		wall_proj_data \
		d_weapon \
		collision_player \
		collision_monster \
		load_sound \
		sound \
		handle_finish \
		handle_respawn \
		init_sdl \
		init_monsters \
		init_monster_type \
		init_projectiles \
		init_player \
		loop \
		handlers \
		events \
		door_use \
		monster_behaviour \
		monster_behaviour_chargingdemon \
		monster_anim_state \
		reorder_sprite \
		create_projectile \
		projectile_collision \
		update \
		color_buffer \
		render_sector \
		clip_wall \
		proj_wall \
		pixel \
		getpixel \
		player_damage \
		load_map \
		load_assets \
		inside \
		fly_mode \
		jumping \
		inertia \
		monster_collision \
		movement \
		get_rot_monster \
		shade \
		swap_list \
		aiming_draw \
		font \
		vector \
		load_monsters_texture \
		n_validators \
		n_allocators \
		height_calculations \
		floor_height \
		ceil_height \
		range \
		msg \
		vector_constructors \
		r_shoot \
		r_shoot2 \
		r_activate \
		circle \
		load_map2 \
		new_font \
		loading2 \
		move_down_vector \
		arrays \
		util_funcs \
		transform \
		newv2_vector \
		newv3_vector \
		to_vector \
		v2_vector \
		vector_min \
		vector_plus \
		render_sector2 \
		vector_scale \
		char_selector \
		loop2 \
		monster_behaviour2 \
		update_2 \
		update_things \
		sprite_things 
LIBFT_DIR = libft/
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))
SDL_CFLAGS = $(shell sdl2-config --cflags)
SPEED = -O3
FLAGSTMP = -Wall -Wextra -Werror
MATH = -lm
HEADERS = -I./includes -I./libft

OS = $(shell uname)
ifeq ($(OS), Linux)
CGFLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
else
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
endif

all: $(NAME)

.PHONY: all clean
.NOTPARALLEL: all $(NAME) clean fclean re

$(NAME): libft/libft.a $(OBJ)
	@echo "\033[36mLinking...\033[0m"
	@$(CC) -o $(NAME) $(FLAGS) $(SPEED) $(OBJ) $(CGFLAGS) ${MATH} $(FRAMEWORKS) libft/libft.a
	@echo "\033[32m[ ✔ ] Binary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
libft/libft.a:
	@make --no-print-directory -j3 -C $(LIBFT_DIR)
obj/%.o: src/%.c
	@$(CC) -o $@ $(FLAGS) $(SPEED) $(HEADERS) $(INCLUDES) -c $^
	@echo "\033[37mCompilation of \033[97m$(notdir $<) \033[0m\033[37mdone. \033[0m"
clean:
	@rm -f $(OBJ)
	@make --no-print-directory -j3 -C libft/ clean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
fclean:
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@make --no-print-directory -j3 -C libft/ fclean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
	@echo "\033[31m[ ✔ ] Binary \033[1;31m$(NAME) \033[1;0m\033[31mremoved.\033[0m"
re: fclean all
