/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:17:14 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/15 17:17:17 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <pthread.h>
# include "../frameworks/SDL2/SDL.h"
# include "../frameworks/SDL2/SDL_render.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

# define WIN_W		1200
# define WIN_H		800
# define MAX_MONS	256
# define MAX_SECT	128
# define MAX_SPRT	64
# define MAX_WALL	32
# define GRID_GAP	16
# define MAX_NAME	100
# define M_NAME_1	"motherdemon"
# define M_NAME_2	"chargingdemon"

# define TEXT_DIR	"../textures"
# define MONSTERS	"../textures/assets/monsters"

typedef enum		e_hight
{
	H_FLOOR,
	H_CEIL,
	H_TOTAL
}					t_hight;

typedef enum		e_tex
{
	T_FLOOR,
	T_WALL,
	T_CEIL,
	T_TOTAL
}					t_tex;

typedef enum		e_mns
{
	M_RANGE,
	M_MELEE,
	M_TOTAL
}					t_mns;

typedef enum		e_type
{
	S_BARREL = 2,
	S_LAMP,
	S_AMMO,
	S_HEAL,
	S_JETPACK,
	S_TOTAL
}					t_type;

typedef	struct		s_v2
{
	int 			x;
	int 			y;
}					t_v2;

typedef struct		s_bmp
{
	char			signature[2];
	int32_t			size;
	int32_t			useless;
	int32_t			offset;
	int32_t			header_size;
	int32_t			width;
	int32_t			height;
	int16_t			planes;
	int16_t			bpp;
	unsigned char	*pixels;
}					t_bmp;

typedef struct		s_wall
{
	int 			n_points;
	t_v2			*points;
	char 			*portals;
	char			is_door;
}					t_wall;

typedef struct		s_spite
{
	char 			type;
	struct s_sprite *next;
}					t_sprite;

typedef struct		s_sect
{
	int 			num;
	short			n_walls;
	t_sprite		*sprites;
	t_wall			*walls;
	short			height[H_TOTAL];
	short			tex[T_TOTAL];
	short			slope[H_TOTAL];
	short			slope_rot[H_TOTAL];
	char 			is_elev;
	char 			is_finish;
	char 			is_dmg;
}					t_sect;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*screen;
}					t_sdl;

typedef	struct		s_seclist
{
	t_sect			*sect;
	t_sect			*next;
	t_sect			*prev;
}					t_seclist;

typedef struct		s_stats
{
	char			sect;
	int 			n_monst;
	int 			n_sect;
	int 			n_sprt;
}					t_stats;

typedef struct		s_v3
{
	double			x;
	double			y;
	double			z;
}					t_v3;

typedef struct		s_texlist
{
	SDL_Surface		*tex;
	int				n_tex;
	char 			name[MAX_NAME];
}					t_texlist;

typedef struct		s_monsters
{
	char 			*name;
	int 			walk;
	int 			attack;
	int 			die;
	int 			w_side;
	int 			a_side;
	SDL_Surface		**walking;
	SDL_Surface		**attacking;
	SDL_Surface		**dying;
}					t_monsters;

typedef struct		s_ed
{
	t_sdl			sdl;
	t_seclist		*seclist;
	t_texlist		*texlist;
	t_monsters		monster[M_TOTAL];
	//t_stats			info;
	int 			fd;
	int 			n_tex;
}					t_ed;

void				print_err(const char *err);
void				init_sdl(t_sdl *sdl);
void				reopen(DIR **dir, const char *path);
void				reopen_fd(int *fd, const char *path);
void				init_textures(t_ed *e);
void 				init_monsters(t_ed *e);
int					bmp_check(struct dirent *data);
void				read_bmp(t_ed *e, int i);
void				loop(t_ed *e);
void				load_names(t_ed *e, char *p, char ***names);

#endif
