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
# include <math.h>
# include "../frameworks/SDL2/SDL.h"
# include "../frameworks/SDL2/SDL_render.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

#define ED_W 1200
#define ED_H 700
# define MAX_MONS	256
# define MAX_SECT	128
# define MAX_SPRT	64
# define MAX_WALL	32
# define GRID_GAP	21
# define MAX_NAME	100
# define BLUE		0x6666FF
# define RED		0xFF6666
# define GRN		0x66FF66
# define DOOR		0x22aF11
# define MGN		0x662266
# define GRID_COL_2 0xa4b60d
# define GRID_COL_1 0x111111
# define SELECTION_FIELD 5
# define M_NAME_1	"motherdemon"
# define M_NAME_2	"chargingdemon"

# define TEXT_DIR	"../textures/"
# define MONSTERS	"../textures/assets/monsters/"

typedef enum
{
	false,
	true
} bool;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

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

typedef enum 		e_anims
{
	A_ATTACK,
	A_WALK,
	A_DIE,
	A_TOTAL
}					t_anims;

typedef enum		e_type
{
	S_BARREL = 3,
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


typedef struct 		s_controller
{
	bool			mouse_is_pressed;
	t_v2			mouse;
}					t_controller;

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
	t_v2			v1;
	t_v2			v2;
	int 			is_portal;
	bool			is_door;
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
	// t_sprite		*sprites;
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
	SDL_Window *win;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	SDL_Surface *screen;
}					t_sdl;

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

typedef struct		s_selection
{
	t_wall			*selected_wall;
	t_v2			*selected_vertex;
	t_v2			*other_vertex;
	t_v2			val;
	int 			port;
	short			drawing;
}					t_selection;

typedef struct		s_monsters
{
	char 			*name;
	int 			anim[A_TOTAL];
	int 			a_rot[A_TOTAL];
	SDL_Surface		**acting[A_TOTAL];
}					t_monsters;

typedef struct		s_ed
{
	t_sdl			sdl;
	t_sect			*seclist;
	t_texlist		*texlist;
	t_wall			*walls;
	t_monsters		monster[M_TOTAL];
	SDL_Surface		**sprites;
	SDL_Surface		*m_projec[5];
	Uint32			*pixels;
	//t_stats			info;
	int 			curr_m;
	int 			fd;
	int 			n_tex;
	int 			n_sprites;
	int 			n_sect;
	int 			n_walls;
	t_selection		selection;
	t_controller	controller;
	t_wall			*initial_walls;
}					t_ed;

void 				sdl_print_pix(Uint32 **pixels, int x, int y);
void				init_sdl(t_sdl *sdl);
void				reopen(DIR **dir, const char *path);
void				reopen_fd(int *fd, const char *path);
void				init_textures(t_ed *e);
void 				init_monsters(t_ed *e);
void				init_sprites(t_ed *e);
t_sect				init_sector(t_wall **walls, int n_walls, int n_s);
int					bmp_check(struct dirent *data);
void				read_bmp(SDL_Surface **s, char *p);
void				loop(t_ed *e);
void				listen_controls(bool *end, t_ed *ed);
void				print_err(const char *err);
void				finish_sector(t_ed *e, int sn);
void				wall_push(t_ed *e, t_v2 v1, t_v2 v2);
void 				init_default_sect(t_ed *e);
int					trim(int v, int inc);
t_v2				trim_v2(t_v2 v);
t_wall				new_wall(int x1, int y1, int x2, int y2);
int					wall_eq(t_wall a, t_wall b);
int					v2_cmp(t_v2 a, t_v2 b);
void				wall_push(t_ed *e, t_v2 v1, t_v2 v2);
void				finish_sector(t_ed *e, int sn);
void 				render_map(t_ed *ed);
void				loop_creation(t_ed *e);
void	sdl_init(t_sdl *sdl);
void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);
void sdl_clean(t_sdl *sdl);
void    sdl_init_renderer(t_sdl *sdl);
void sdl_clear_texture(Uint32 **pixels);
Uint32 *get_screen_pixels(void);
void				load_names(t_ed *e, char *p, int i);
void render_manager(t_sdl *sdl, t_ed *ed);
void sdl_apply_renderer(t_sdl *sdl, t_ed *ed);
void line(t_v2 p1, t_v2 p2, t_ed *ed, Uint32 color);
void bold_line(t_v2 p1, t_v2 p2, t_ed *ed, Uint32 color);
t_v2 new_v2(int a, int b);
bool v2_compare(t_v2 a, t_v2 b, int r);
int			mouse_controller(t_ed *ed, SDL_Event *event);
bool		corner_selected(t_ed *ed);
bool		sector_selected(t_ed *ed);
#endif
