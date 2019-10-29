/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:17:14 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:51:39 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include "../frameworks/SDL2/SDL.h"
# include "../frameworks/SDL2/SDL_render.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

# define ED_W		1200
# define ED_H		700
# define MAX_MONS	32
# define MAX_SECT	128
# define MAX_SPRT	64
# define MAX_WALL	512
# define GRID_GAP	21
# define MAX_NAME	100
# define PICKER_SIZE 100
# define BLUE		0x6666FF
# define RED		0xFF6666
# define GRN		0x66FF66
# define DOOR		0x2244aa
# define GRID_COL_2 0xa4b60d
# define GRID_COL_1 0x111111
# define MOSTER_1_PICKER_W	1000
# define FIRST_SPRITE_W		900
# define FIRST_SPRITE_H		350
# define MOSTER_2_PICKER_W	1120
# define MOSTER_PICKER_H 	450
# define SHAPE_SIZE			50
# define SELECTION_FIELD	5
# define MAX_SOUND			5000000
# define M_NAME_1			"motherdemon"
# define M_NAME_2			"chargingdemon"

# define TEXT_DIR	"../texts/"
# define MONSTERS	"../texts/objects/monsters/"

typedef	enum	e_bool
{
	false,
	true
}				t_bool;

# define MAX(a, b) (((a) > (b)) ? (a) : (b))
# define MIN(a, b) (((a) > (b)) ? (b) : (a))

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

typedef enum		e_edit
{
	E_SLOPE = 2,
	E_SLOPE_ROT,
	E_FLOOR,
	E_CEIL,
	E_FLOOR_TEX,
	E_WALL_TEX,
	E_CEIL_TEX,
	E_DANGER,
	E_ELEVATOR,
	E_EXIT
}					t_edit;

typedef enum		e_anims
{
	A_ATTACK,
	A_WALK,
	A_DIE,
	A_TOTAL
}					t_anims;

typedef enum		e_pos
{
	P_FLOOR,
	P_CEIL
}					t_pos;

typedef	struct		s_v2
{
	int				x;
	int				y;
}					t_v2;

typedef struct		s_controller
{
	t_bool			mouse_is_pressed;
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

typedef struct		s_bitmap
{
	int				bit[8];
}					t_bitmap;

typedef struct		s_chars
{
	t_bitmap			b;
	t_bitmap			a;
	t_bitmap			c;
	t_bitmap			d;
	t_bitmap			e;
	t_bitmap			f;
	t_bitmap			g;
	t_bitmap			h;
	t_bitmap			i;
	t_bitmap			j;
	t_bitmap			k;
	t_bitmap			l;
	t_bitmap			m;
	t_bitmap			n;
	t_bitmap			o;
	t_bitmap			p;
	t_bitmap			q;
	t_bitmap			r;
	t_bitmap			s;
	t_bitmap			t;
	t_bitmap			u;
	t_bitmap			v;
	t_bitmap			w;
	t_bitmap			x;
	t_bitmap			y;
	t_bitmap			z;
	t_bitmap			dot;
	t_bitmap			exc;
	t_bitmap			semi;
	t_bitmap			spc;
	t_bitmap			n0;
	t_bitmap			n1;
	t_bitmap			n2;
	t_bitmap			n3;
	t_bitmap			n4;
	t_bitmap			n5;
	t_bitmap			n6;
	t_bitmap			n7;
	t_bitmap			n8;
	t_bitmap			n9;
	t_bitmap			slh;
	t_bitmap			prc;
}					t_chars;

typedef struct		s_wall
{
	t_v2			v1;
	t_v2			v2;
	int				is_portal;
	t_bool			is_door;
	int				tex[T_TOTAL];
}					t_wall;

typedef struct		s_sprite
{
	char			name[MAX_NAME];
	SDL_Surface		*texture;
	char			pos;
	char			sect;
	char			interactive;
	char			autopick;
	char			collision;
	char			jetpack;
	char			key;
	int				k_num;
	short			heal;
	short			dmg;
	short			ammo;
}					t_sprite;

typedef struct		s_sect
{
	int				num;
	short			n_walls;
	int				n_sprt;
	int				start_wall;
	t_wall			*walls;
	short			height[H_TOTAL];
	short			tex[T_TOTAL];
	short			slope[H_TOTAL];
	short			slope_rot[H_TOTAL];
	char			is_elev;
	char			is_finish;
	char			is_dmg;
}					t_sect;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Event		event;
	SDL_Surface		*screen;
}					t_sdl;

typedef struct		s_stats
{
	char			sect;
	int				n_monst;
	int				n_sect;
	int				n_sprt;
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
	char			name[MAX_NAME];
}					t_texlist;

typedef struct		s_selection
{
	t_wall			*selected_wall;
	t_v2			*selected_vertex;
	t_v2			*other_vertex;
	t_v2			val;
	int				port;
	short			drawing;
	short			sector;
	int				monster;
	int				select;
	int				sprite;
}					t_selection;

typedef struct		s_spl
{
	int16_t			id;
	struct s_spl	*next;
	uint8_t			type;
}					t_sprite_list;

typedef struct		s_stdsector
{
	int16_t			firstwallnum;
	int16_t			n_walls;
	float			floorheight;
	float			ceilheight;
	int16_t			floorpicnum;
	int16_t			ceilpicnum;
	float			light;
	char			blinking;
	char			floor_texture_name[100];
	char			ceil_texture_name[100];
	char			outdoor;
	t_sprite_list	*sprite_list;
	int16_t			slope;
	int16_t			slope_orientation;
	int16_t			slopeceil;
	int16_t			slopeceil_orientation;
	char			is_animatedslope;
	char			is_animatedslopeceil;
	char			is_elevator;
	char			is_finish;
	char			is_harmful;
}					t_sdtsector;

typedef struct		s_monsters
{
	char			*name;
	int				anim[A_TOTAL];
	int				a_rot[A_TOTAL];
	SDL_Surface		**acting[A_TOTAL];
}					t_monsters;

typedef struct		s_v2f
{
	double			a;
	double			b;
}					t_v2f;

typedef struct		s_stdwall
{
	t_v2f			point;
	int16_t			upperpicnum;
	int16_t			middlepicnum;
	int16_t			lowerpicnum;
	int16_t			flags;
	int16_t			neighborsect;
	char			texture_name[100];
	char			poster_name[100];
	char			is_door;
	int				door_num;
	int				key_num;
	int16_t			posterpicnum;
	char			is_transparent;
}					t_stdwall;

typedef struct		s_font
{
	int				x;
	int				y;
	char			*str;
	int				col;
	int				n;
}					t_font;

typedef struct		s_mnst
{
	t_v2			pos;
	int				n_sect;
	int				type;
}					t_mnst;

typedef struct		s_sprt
{
	t_v2			pos;
	int				n_sect;
	int				type;
}					t_sprt;

typedef struct		s_stdmonster
{
	t_v2f			pos;
	t_v2f			dir;
	double			rot;
	int16_t			this_sect;
	uint8_t			id_type;
	uint8_t			anim_state;
	uint8_t			anim_time;
	uint8_t			timer;
	int16_t			life;
	char			can_collide;
	char			activated;
}					t_stdmonster;

typedef struct		s_smd
{
	int16_t			heal;
	int16_t			damage;
	int16_t			ballista_ammo;
	int16_t			blaster_ammo;
	int16_t			m16_ammo;
}					t_smd;

typedef struct		s_stdast
{
	int				objects_n;
	int				picnum;
	t_v2f			world_pos;
	char			is_on_floor;
	char			is_on_ceil;
	t_smd			stat_mod;
	char			is_interactive;
	char			is_autopick;
	char			collision;
	char			is_jetpack;
	char			is_key;
	int				key_num;
	char			used;
}					t_stdast;

typedef struct		s_ed
{
	t_sdl			sdl;
	t_sect			*seclist;
	t_texlist		*texlist;
	int				n_tex;
	char			*used_tex;
	t_wall			*walls;
	int				n_all_w;
	t_monsters		monster[M_TOTAL];
	t_sprite		*sprites;
	SDL_Surface		*m_projec[5];
	Uint32			*pixels;
	t_chars			chars;
	int				curr_m;
	int				fd;
	int				n_sprites;
	int				n_sect;
	int				n_walls;
	char			*path;
	t_v3			player;
	double			p_ang;
	uint16_t		start;
	SDL_Surface		*texture_picker;
	t_selection		selection;
	t_controller	controller;
	int				n_mns;
	t_mnst			monst[MAX_MONS];
	int				n_sprt;
	t_sprt			sprt[MAX_SPRT];
	int				n_used_tex;
	char			*weapon[3][2][20];
	SDL_Surface		*wp_tex[3][20];
	SDL_Surface		*wp_p[3][20];
	Uint32			color;
}					t_ed;

void				sdl_print_pix(Uint32 **pixels, int x, int y);
void				init_sdl(t_sdl *sdl);
void				reopen(DIR **dir, const char *path);
void				reopen_fd(int *fd, const char *path);
void				init_textures(t_ed *e);
void				init_monsters(t_ed *e);
void				init_sprites(t_ed *e);
t_sect				init_sector(t_wall **walls, int n_walls, int n_s);
void				find_used_tex(t_ed *e);
int					bmp_check(struct dirent *data);
void				read_bmp(SDL_Surface **s, char *p);
void				loop(t_ed *e);
void				listen_controls(t_bool *end, t_ed *ed);
void				print_err(const char *err);
void				finish_sector(t_ed *e);
void				wall_push(t_ed *e, t_v2 v1, t_v2 v2, short port);
void				init_default_sect(t_ed *e);
char				*add_path(char *p);
int					trim(int v, int inc);
t_v2				trim_v2(t_v2 v);
t_wall				new_wall(int x1, int y1, int x2, int y2);
int					wall_eq(t_wall a, t_wall b);
int					v2_cmp(t_v2 a, t_v2 b);
void				render_map(t_ed *ed);
void				render_sector(t_ed *ed, t_sect *s);
void				loop_creation(t_ed *e);
int					intersects(t_v2 l[2], t_sect *s);
int					in_range(double t);
void				sdl_init(t_sdl *sdl);
void				sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);
void				draw_selection(t_ed *ed);
void				draw_mouse_highlight(t_ed *ed, t_v2 mouse);
void				sdl_clean(t_sdl *sdl);
void				sdl_init_renderer(t_sdl *sdl);
void				sdl_clear_texture(Uint32 **pixels);
Uint32				*get_screen_pixels(void);
void				load_names(t_ed *e, char *p, int i);
void				render_manager(t_sdl *sdl, t_ed *ed);
void				sdl_apply_renderer(t_sdl *sdl, t_ed *ed);
void				line(t_v2 p1, t_v2 p2, t_ed *ed, Uint32 color);
void				bold_line(t_v2 p1, t_v2 p2, t_ed *ed, Uint32 color);
t_v2				new_v2(int a, int b);
void				init_font(t_ed *d);
void				draw_info(t_ed *e);
void				draw_string(t_ed *d, t_font f);
t_bool				v2_compare(t_v2 a, t_v2 b, int r);
int					mouse_controller(t_ed *ed, SDL_Event *event);
t_bool				corner_selected(t_ed *ed);
t_bool				sector_selected(t_ed *ed);
void				render_texture_picker(t_ed *ed);
void				render_monsters(t_ed *ed, t_sdl *sdl);
void				render_sprites(t_ed *ed, t_sdl *sdl);
void				render_picker(t_ed *ed, t_sdl *sdl);
int					circle(t_ed *ed, t_v2 c, int r, Uint32 color);
int					picking_monster(t_v2 mouse);
int					picking_sprite(t_v2 mouse, int n);
void				draw_bitmap(t_ed *d, t_bitmap bitmap, t_font f);
void				draw_char(t_ed *d, t_font f);
int					pickers(t_ed *ed);
void				save_world(t_ed *e, char *path);
void				write_secors(t_ed *e);
void				write_monsters(t_ed *e);
void				write_sprites(t_ed *e);
void				write_tex_list(t_ed *e);
void				write_tex_data(t_ed *e);
void				write_posters(t_ed *e);
void				write_weapon(t_ed *e);
void				load_wp_tex(t_ed *e, const int n_tex[3], const int n_p[3]);
void				save_wp_tex(t_ed *e, int n_tex[3], int n_p[3]);
void				write_mons_tex(t_ed *e);
void				write_sprt_tex(t_ed *e);
void				put_monster(t_ed *ed, int n_sect);
void				put_sprite(t_ed *ed, int n_sect);
void				render_sector_sprites(t_ed *ed);
void				render_sector_mosters(t_ed *ed);
void				print_v(t_v2 v, const char *s);
void				draw_square(t_ed *ed, t_v2 c, int r, Uint32 col);

#endif
