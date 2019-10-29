/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:23:09 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 23:23:47 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "../frameworks/SDL2/SDL.h"
# include "../frameworks/SDL2/SDL_render.h"
# include "../libft/libft.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <limits.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <math.h>

# define MAXNUMSECTORS 1024
# define MAXNUMMONSTERS 256
# define MAXNUMWALLS 4096
# define MAXTYPEMONSTERS 2
# define DOUBLE_PI 		(2 * M_PI)

typedef struct				s_vec3f
{
	double					x;
	double					y;
	double					z;
}							t_vec3f;

typedef struct				s_vec2f
{
	double					x;
	double					y;
}							t_vec2f;

typedef struct				s_vec2
{
	int						x;
	int						y;
}							t_vec2;

# define IS_PROJECTILE 0
# define IS_MONSTER 1
# define CRYO_BALLISTA 0
# define FIREBALL_1 1
# define MOTHERDEMON 0
# define CHARGINGDEMON 1

t_vec3f						new_v3(double x, double y, double z);
t_vec2f						new_v2(double x, double y);
t_vec2f						v2_min(t_vec2f v1, t_vec2f v2);
t_vec2f						v2_plus(t_vec2f v1, t_vec2f v2);
void						actualize_dir(double angle, t_vec2f *vec);
t_vec3f						v3_min(t_vec3f v1, t_vec3f v2);
t_vec3f						v3_scale(t_vec3f v1, double scalar);

t_vec2f						v2_scale(t_vec2f v, double scalar);
float						v2_dot(t_vec2f v);
double						v2_len(t_vec2f v);
double						v2_atan(t_vec2f v1, t_vec2f v2);
t_vec3f						v3_plus(t_vec3f a, t_vec3f b);

typedef struct				s_font
{
	char					*str;
	int						x;
	int						y;
	uint32_t				color;
	int						scale;
}							t_font;

typedef struct				s_sprite_list
{
	int16_t					id;
	struct s_sprite_list	*next;
	uint8_t					type;
}							t_sprite_list;

typedef struct				s_sprite
{
	int16_t					id;
	uint8_t					type;
}							t_sprite;

typedef struct				s_sector
{
	int16_t					firstwallnum;
	int16_t					numwalls;
	float					floorheight;
	float					ceilheight;
	int16_t					floorpicnum;
	int16_t					ceilpicnum;
	float					light;
	bool					blinking;
	char					floor_texture_name[100];
	char					ceil_texture_name[100];
	bool					outdoor;
	t_sprite_list			*sprite_list;
	int16_t					slope;
	int16_t					slope_orientation;
	int16_t					slopeceil;
	int16_t					slopeceil_orientation;
	bool					is_animatedslope;
	bool					is_animatedslopeceil;
	bool					is_elevator;
	bool					is_finish;
	bool					is_harmful;
}							t_sector;

typedef struct				s_wall
{
	t_vec2f					point;
	int16_t					upperpicnum;
	int16_t					middlepicnum;
	int16_t					lowerpicnum;
	int16_t					flags;
	int16_t					neighborsect;
	char					texture_name[100];
	char					poster_name[100];
	bool					is_door;
	int						door_num;
	int						key_num;
	int16_t					posterpicnum;
	bool					is_transparent;
}							t_wall;

typedef struct				s_stat_modifier
{
	int16_t					heal;
	int16_t					damage;
	int16_t					ballista_ammo;
	int16_t					temp1;
	int16_t					temp2;
}							t_stat_modifier;

typedef struct				s_assets
{
	int						nb_assets;
	int						picnum;
	t_vec2f					world_pos;
	bool					is_on_floor;
	bool					is_on_ceil;
	t_stat_modifier			stat_mod;
	bool					is_interactive;
	bool					is_autopick;
	bool					collision;
	bool					is_jetpack;
	bool					is_key;
	int						key_num;
	bool					used;
}							t_assets;

typedef struct				s_monster
{
	t_vec2f					pos;
	t_vec2f					dir;
	double					rot;
	int16_t					cursectnum;
	uint8_t					id_type;
	uint8_t					anim_state;
	uint8_t					anim_time;
	uint8_t					timer;
	int16_t					life;
	bool					can_collide;
	bool					activated;
}							t_monster;

# define WIDTH 800
# define HEIGHT 600
# define MUST_BE_DESTROYED 255
# define FPS 60
# define MAX_Y_OFFSET (HEIGHT/2)
# define PLAYER_HITBOX 0.1

typedef struct				s_display_data
{
	t_vec2f					start;
	t_vec2f					end;
	t_vec2f					scale;
	int						cut_start;
	int						cut_end;
	int						*ytop;
	int						*ybot;
	uint16_t				cursectnum;
}							t_display_data;

typedef struct				s_col_inf
{
	t_vec3f					pos;
	bool					ok;
}							t_col_inf;

typedef	struct				s_v2_pair
{
	t_vec2f					v1;
	t_vec2f					v2;
}							t_v2_pair;

typedef struct				s_range {
	int						min;
	int						max;
	double					t;
}							t_range;

typedef struct				s_cam
{
	t_vec3f					pos;
	double					rot;
	double					sin;
	double					cos;
	double					y_offset;
}							t_cam;

typedef struct				s_frustum
{
	int						ytop[WIDTH];
	int						ybottom[WIDTH];
	int						x1;
	int						x2;
	bool					visitedportals[MAXNUMWALLS];
}							t_frustum;

typedef struct				s_projdata
{
	double					x1;
	double					x2;
	int						cx1;
	int						cx2;
	double					z1;
	double					z2;
	int						y1a;
	int						y2a;
	int						y1b;
	int						y2b;
	int						y1c;
	int						y2c;
	int						y1d;
	int						y2d;
	t_sector				*neighbor;
	int						ny1a;
	int						ny2a;
	int						ny1b;
	int						ny2b;
	double					u1;
	double					u2;
	double					y_scale;
	t_wall					*wall;
	t_wall					*wall2;
	t_sector				*sector;
	double					n;
	double					z;
	int						x;
	int						y;
	double					u;
	int						ya;
	int						yb;
	int						yc;
	int						yd;
	int						nya;
	int						nyb;
	double					zbuffer[WIDTH];
	bool					visible[WIDTH];
	double					doorheight;
	double					doorbottom;
	double					u1_poster;
	double					u2_poster;
	double					poster_h;
	t_vec3f					v[3];
	t_vec3f					c[3];
	double					area;
	t_vec3f					a[3];
	t_vec3f					b[3];
	double					areaa;
	bool					is_on_floor;
	double					shadefactor;
	double					len;
	double					scale1;
	double					scale2;
	int						u_tex;
	int						u_poster;
	SDL_Surface				*tex;
	SDL_Surface				*poster;
	int						ya_poster;
	int						yb_poster;
	int						margin;
}							t_projdata;

# define MAX_STATE_OF_PROJ_ANIM 21
# define COLLISION_ID MAX_STATE_OF_PROJ_ANIM - 1

typedef struct				s_anim_rot
{
	bool					is_active;
	bool					has_collided;
	uint8_t					id_type;
	uint16_t				cursectnum;
	t_vec3f					pos;
	t_vec3f					dir;
	uint8_t					weapon_id;
	uint8_t					time_remaining_anim;
	uint8_t					current_anim_playing;
	t_monster				*target;
}							t_anim_rot;

typedef struct				s_proj_type
{
	double					hitbox_radius;
	double					speed;
	double					size;
	uint16_t				damage;
	uint8_t					anim_order[MAX_STATE_OF_PROJ_ANIM];
	uint8_t					kind;
	bool					threat_to_player;
	bool					threat_to_monster;
}							t_proj_type;

typedef struct				s_weapon_type
{
	uint8_t					rate_of_fire[2];
	uint8_t					time_to_reload[2];
	uint8_t					shooting_type[2];
	uint8_t					left_projectile;
	uint8_t					right_projectile;
	uint16_t				temp;
	uint16_t				current_ammo;
	bool					has_alt_fire;
}							t_weapon_type;

# define MAX_STATE_MONSTER 20

typedef struct				s_monster_type
{
	double					height;
	double					size;
	uint16_t				health;
	double					floating;
	double					hitbox_radius;
	uint8_t					id_of_proj;
	uint8_t					anim_order[MAX_STATE_MONSTER];
}							t_monster_type;

# define MAX_KIND_OF_WEAP 3
# define MAX_ANIM_PER_WEAP 15
# define LEFT_CLICK 1
# define RIGHT_CLICK 2

typedef	struct				s_player
{
	int16_t					health;
	uint8_t					can_be_stomped;
	uint8_t					current_weapon;
	uint8_t					charging;
	uint8_t					can_shoot;
	uint8_t					timer_change_weap;
	uint8_t					timer_anim_weap;
	uint8_t					current_anim_playing;
	uint8_t					speed_anim[MAX_KIND_OF_WEAP];
	uint8_t					weapon_anim[MAX_KIND_OF_WEAP][MAX_ANIM_PER_WEAP];
	uint8_t					click;
	uint16_t				is_flying;
	uint8_t					can_move;
	double					minimum_height;
	double					gravity;
}							t_player;

# define MAX_BUF_VALUE 240

typedef struct				s_color_buf
{
	uint32_t				colo;
	int16_t					value;
}							t_color_buf;

# define MAXNBOFANIMATION 5
# define MAX_PROJECTILE_TEX_PER_WEAP MAX_STATE_OF_PROJ_ANIM
# define MAX_KIND_OF_PROJECTILE 3
# define MAX_PROJECTILES 100
# define MOUSE_PRESSED 1
# define MOUSE_RELEASED 2
# define MOUSE_NO_ACTION 3
# define NB_OF_SOUNDS 20

typedef struct				s_sdl {
	SDL_Window				*win;
	SDL_Surface				*screen;
	TTF_Font				*font;
}							t_sdl;

typedef struct				s_scene {
	SDL_Window				*win;
	SDL_Surface				*screen;
}							t_scene;

typedef struct				s_bitmap
{
	int						bit[8];
}							t_bitmap;

typedef struct				s_chars
{
	t_bitmap				b;
	t_bitmap				a;
	t_bitmap				c;
	t_bitmap				d;
	t_bitmap				e;
	t_bitmap				f;
	t_bitmap				g;
	t_bitmap				h;
	t_bitmap				i;
	t_bitmap				j;
	t_bitmap				k;
	t_bitmap				l;
	t_bitmap				m;
	t_bitmap				n;
	t_bitmap				o;
	t_bitmap				p;
	t_bitmap				q;
	t_bitmap				r;
	t_bitmap				s;
	t_bitmap				t;
	t_bitmap				u;
	t_bitmap				v;
	t_bitmap				w;
	t_bitmap				x;
	t_bitmap				y;
	t_bitmap				z;
	t_bitmap				dot;
	t_bitmap				exc;
	t_bitmap				semi;
	t_bitmap				spc;
	t_bitmap				n0;
	t_bitmap				n1;
	t_bitmap				n2;
	t_bitmap				n3;
	t_bitmap				n4;
	t_bitmap				n5;
	t_bitmap				n6;
	t_bitmap				n7;
	t_bitmap				n8;
	t_bitmap				n9;
	t_bitmap				slh;
	t_bitmap				prc;
}							t_chars;

typedef struct				s_env
{	t_sdl					sdl;
	t_scene					scene;
	t_player				player;
	SDL_Surface				**texts;
	int32_t					n_texts;
	SDL_Surface				**posters;
	int32_t					n_posters;
	SDL_Surface				**assets_texture;
	int16_t					nb_assets_texture;
	char					**tex_name_list;
	SDL_Surface				*monster_text[MAXTYPEMONSTERS]
	[MAX_STATE_MONSTER][MAXNBOFANIMATION];
	SDL_Surface				*projectile_tex[MAX_KIND_OF_PROJECTILE]
	[MAX_PROJECTILE_TEX_PER_WEAP];
	SDL_Surface				*weapon_tex[MAX_KIND_OF_WEAP]
	[MAX_ANIM_PER_WEAP];
	Uint8					*keys;
	uint8_t					left_mouse_button;
	uint8_t					right_mouse_button;
	t_cam					startcam;
	t_cam					cam;
	t_sector				sectors[MAXNUMSECTORS];
	t_wall					walls[MAXNUMWALLS];
	t_monster				*monsters;
	t_assets				**assets;
	int16_t					nb_assets;
	t_monster_type			monster_type[MAXTYPEMONSTERS];
	t_anim_rot				anim_rots[MAX_PROJECTILES];
	t_proj_type				projectile_type[MAX_KIND_OF_PROJECTILE];
	t_weapon_type			weapon_type;
	uint16_t				nummonsters;
	int16_t					numsectors;
	int16_t					numwalls;
	int16_t					startsectnum;
	int16_t					cursectnum;
	bool					debug_pause;
	double					dooranimstep[MAXNUMWALLS];
	double					doorstate[MAXNUMWALLS];
	double					lightblink;
	t_color_buf				color_buf;
	t_vec2f					inertia;
	unsigned char			font[96][5];
	int						used[96];
	double					*zbuffer;
	double					floorheightplayer;
	double					ceilheightplayer;
	char					nextmap[100];
	Mix_Chunk				*chunk[NB_OF_SOUNDS];
	t_assets				*slot2;
	t_assets				*slot3;
	char					msg[100];
	uint32_t				msg_start;
	uint32_t				last_dangerous_area_damage;
	int						difficulty;
	t_chars					chars;
	int						loaded;
	TTF_Font				*g_font;
	unsigned int			tick;
}							t_env;

typedef struct				s_thread_arg
{
	t_env					*d;
	t_projdata				*p;
	t_frustum				*fr;
}							t_thread_arg;

typedef	struct				s_args_multi_colo_buf
{
	t_env					*d;
	short					start_x;
	short					max_x;
}							t_args_multi_colo_buf;

typedef	struct				s_three_val
{
	int						one;
	int						two;
	int						three;
}							t_three_val;

# define COLLISION_DIST 0.2
# define MINIMUM_HEIGHT_TO_WALK 0.32
# define MINIMUM_CEIL_DIST 0.1

# define MIN_HEIGHT_MONSTER_TO_WALK 1
# define SMALLEST_HEIGHT_FOR_MONSTERS 1.4

# define ANIMATION_TIME (SDL_GetTicks() / 1000.0)
# define D double
# define CLAMP(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
# define NORMALIZE(v, m, x) ((((D)v) - ((D)m)) / (((D)x) - ((D)m)))
# define MOD(i, n) (((i) % (n) + (n)) % (n))
# define LERP(n, m, x) (((D)m) * (1 - ((D)n)) + ((D)x) * ((D)n))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))
# define MIN(a, b) (((a) > (b)) ? (b) : (a))

# define INCREMENT true
# define SET false

# define MAX_BULLETS 30
# define COLLISION_R 0.8

# define MAX_FUEL 500
# define FUEL 300

# define BLASTER_HITBOX 0.4
# define LEFT_MOUSE_BLASTER_DAMAGE 35
# define RIGHT_MOUSE_BLASTER_DAMAGE 35

# define MAX_THREADS 8

# define NB_TEX (int[3]){13, 15, 3}
# define NB_PROJECTILE (int[3]){20, 0, 5}
# define DIST_COLL_PROJ_CEIL_FLOOR 0.1
# define TRANSLATE_WEAP_TIME 30
# define MONSTER_MIN_DIST_HITBOX 0.15
# define MINIMUM_SIZE_AROUND_MONSTERS 0.8
# define FLYING_SPEED 0.01
# define NB_MENU_ITEMS 3
# define M "  I'M TOO YOUNG TO DIE.\n  HEY, NOT TOO ROUGH.\n  HURT ME PLENTY."
# define CROUCH_SPEED 0.01
# define COLLISION_RANGE_CHARGINGDEMON 0.2
# define TURN_SPEED 0.02

# define DEPTH_TO_SCAN 10

# define MINIMUM_HEIGHT_TO_WALK 0.32
# define MOVE_SPEED 0.02
# define MINIMUM_HEIGHT_OF_WALKABLE_SECTOR 0.6

# define Y_OFFSET_TO_ROT -0.00125

# define ACTIVATION_RADIUS 6
# define LONG_RANGE 7
# define COLLISION_DIST_MOTHERDEMON 1.0

# define SIZE_OF_WEAP 1.5;
# define MAX_INERTIA 0.19

# define ACTIVATION_DIST 3.0

# define Y_OFFSET_TO_ROT -0.00125

# define NB_OF_SECTOR_DEPTH 2

# define C0 {0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0xbe,0x00,0x00}
# define C1 {0x00,0x07,0x00,0x07,0x00},{0x48,0xfc,0x48,0xfc,0x48}
# define C2 {0x48,0x54,0xfe,0x54,0x24},{0x88,0x54,0x28,0x50,0xa8}
# define C3 {0x6c,0x92,0x92,0xac,0x40},{0x00,0x00,0x07,0x00,0x00}
# define C4 {0x00,0x7c,0x82,0x01,0x00},{0x00,0x01,0x82,0x7c,0x00}
# define C5 {0x28,0x10,0x7c,0x10,0x28},{0x10,0x10,0x7c,0x10,0x10}
# define C6 {0x00,0x40,0x20,0x00,0x00},{0x10,0x10,0x10,0x10,0x10}
# define C7 {0x00,0x00,0x80,0x00,0x00},{0x00,0xc0,0x30,0x0c,0x03}
# define C8 {0x7c,0x82,0x92,0x82,0x7c},{0x00,0x84,0xfe,0x80,0x00}
# define C9 {0xc4,0xa2,0x92,0x92,0x8c},{0x44,0x82,0x92,0x92,0x6c}
# define C10 {0x30,0x28,0x24,0xfe,0x20},{0x5e,0x92,0x92,0x92,0x62}
# define C11 {0x78,0x94,0x92,0x92,0x60},{0x02,0x82,0x62,0x1a,0x06}
# define C12 {0x6c,0x92,0x92,0x92,0x6c},{0x0c,0x92,0x92,0x52,0x3c}
# define C13 {0x00,0x00,0x48,0x00,0x00},{0x00,0x80,0x48,0x00,0x00}
# define C14 {0x10,0x10,0x28,0x28,0x44},{0x28,0x28,0x28,0x28,0x28}
# define C15 {0x44,0x28,0x28,0x10,0x10},{0x04,0x02,0xa2,0x12,0x0c}
# define C16 {0x7c,0x82,0xba,0xba,0xa2},{0xe0,0x38,0x26,0x38,0xe0}
# define C17 {0xfe,0x92,0x92,0x92,0x6c},{0x7c,0x82,0x82,0x82,0x44}
# define C18 {0xfe,0x82,0x82,0x44,0x38},{0xfe,0x92,0x92,0x92,0x82}
# define C19 {0xfe,0x12,0x12,0x12,0x02},{0x7c,0x82,0x82,0x92,0xf4}
# define C20 {0xfe,0x10,0x10,0x10,0xfe},{0x00,0x82,0xfe,0x82,0x00}
# define C21 {0x80,0x80,0x82,0x82,0x7e},{0xfe,0x10,0x28,0x44,0x82}
# define C22 {0xfe,0x80,0x80,0x80,0x80},{0xfe,0x18,0x60,0x18,0xfe}
# define C23 {0xfe,0x06,0x38,0xc0,0xfe},{0x7c,0x82,0x82,0x82,0x7c}
# define C24 {0xfe,0x12,0x12,0x12,0x0c},{0x7c,0x82,0x82,0xc2,0xfc}
# define C25 {0xfe,0x12,0x12,0x12,0xec},{0x4c,0x92,0x92,0x92,0x64}
# define C26 {0x02,0x02,0xfe,0x02,0x02},{0x7e,0x80,0x80,0x80,0x7e}
# define C27 {0x0e,0x30,0xc0,0x30,0x0e},{0x1e,0xe0,0x1c,0xe0,0x1e}
# define C28 {0xc6,0x28,0x10,0x28,0xc6},{0x0e,0x10,0xf0,0x10,0x0e}
# define C29 {0xc2,0xa2,0x92,0x8a,0x86},{0x00,0xff,0x01,0x01,0x00}
# define C30 {0x03,0x0c,0x30,0xc0,0x00},{0x00,0x01,0x01,0xff,0x00}
# define C31 {0x08,0x04,0x02,0x04,0x08},{0x00,0x00,0x00,0x00,0x00}
# define C32 {0x00,0x00,0x02,0x04,0x00},{0x40,0xa8,0xa8,0xa8,0xf0}
# define C33 {0xff,0x88,0x88,0x88,0x70},{0x70,0x88,0x88,0x88,0x88}
# define C34 {0x70,0x88,0x88,0x88,0xff},{0x70,0xa8,0xa8,0xa8,0xb0}
# define C35 {0x08,0xfe,0x09,0x09,0x01},{0x70,0x88,0x88,0x88,0xf0}
# define C36 {0xff,0x08,0x08,0x08,0xf0},{0x00,0x08,0xfa,0x00,0x00}
# define C37 {0x00,0x00,0x08,0xfa,0x00},{0x00,0xff,0x20,0x50,0x88}
# define C38 {0x00,0x01,0xff,0x00,0x00},{0xf8,0x08,0xf0,0x08,0xf0}
# define C39 {0xf8,0x08,0x08,0x08,0xf0},{0x70,0x88,0x88,0x88,0x70}
# define C40 {0xfe,0x22,0x22,0x22,0x1c},{0x1c,0x22,0x22,0x22,0xfe}
# define C41 {0xf8,0x10,0x08,0x08,0x10},{0x90,0xa8,0xa8,0xa8,0x48}
# define C42 {0x00,0x7e,0x88,0x88,0x80},{0x78,0x80,0x80,0x80,0xf8}
# define C43 {0x18,0x60,0x80,0x60,0x18},{0x38,0xc0,0x30,0xc0,0x38}
# define C44 {0x88,0x50,0x20,0x50,0x88},{0x1e,0xa0,0xa0,0xa0,0x7e}
# define C45 {0x88,0xc8,0xa8,0x98,0x88},{0x00,0x10,0xee,0x01,0x00}
# define C46 {0x00,0x00,0xff,0x00,0x00},{0x00,0x01,0xee,0x10,0x00}
# define C47 {0x20,0x10,0x10,0x20,0x20},{0x00,0x00,0x00,0x00,0x00}

# define MOUSE_SENSITIVTY 1
# define CHAR_WIDTH 5
# define CHAR_HEIGHT 8

# define MINIMUM_HEIGHT 0.5

# define MAX_INERTIA 0.19

# define SPEED_ANIM 10
# define SPEED_ANIM_CHARG 7
# define SPEED_ANIM_CHOW 17
# define MOTHER_DEMON_ATTACK 6

# define BOUNCING_DIST_PROJ 0.12
# define BOUNCING_DIST_MOTHERDEMON 0.1
# define BOUCING_DIST_CHARGINGDEMON 0.18

# define MIN_DIST_TO_PLAYER 0.15

# define NB_OF_SECTOR_DEPTH 2

# define SLOT_W 64

# define WEAP_NAME (char*[]){"cryo_ballista/", "blaster/", "m16/"}
# define NB_TEX (int[3]){13, 15, 3}
# define NB_PROJECTILE (int[3]){20, 0, 5}

# define MAX_SIZE_FOR_SOUND 5000000

# define COLOR_SELECT 0x009900
# define PATH_MAP "./maps/"
# define POSTER_W 1.3
# define MINIMUM_HEIGHT 0.5
# define MAIN_MUSIC 0
# define CRYO_SOUND 2
# define EXPLOSION_SOUND 4
# define PLAYER_FELL_SOUND 5
# define PLAYER_GOT_HIT_SOUND 6
# define PLAYER_DEATH_SOUND 7
# define CHARG_AGRO_SOUND 8
# define CHARG_ATK_SOUND 9
# define CHARG_DEATH_SOUND 10
# define MOTHER_AGRO_SOUND 11
# define MOTHER_ATK_SOUND 12
# define MOTHER_DEATH_SOUND 13
# define AMMO_SOUND 15
# define HEALTH_SOUND 16
# define OPEN_DOOR_SOUND 17
# define CLOSE_DOOR_SOUND 18
# define PIKA_SONG 19
# define MAX_CHANNELS 100
# define MINIMUM_CROUCH_HEIGHT 0.2
# define MINIMUM_CEIL_DIST 0.1
# define JUMP_FIX 0.01
# define JUMP_FORCE 0.08
# define EASY 0
# define NORMAL 1
# define HARD 2
# define RED 0xFF0000
# define PURPLE 0x800080
# define GREEN_BLAST 0x5CE26E
# define HEALTH_COLO 0xFFFF66
# define SAME_POS(v1, v2) (((v1.x) == (v2.x)) && ((v1.y) == (v2.y)))
# define F_ANIM 1
# define PICKUP_RANGE 2

void						change_buf_colo(t_env *d, uint16_t amount,
															uint32_t colo);
double						get_dist(t_vec2f a, t_vec2f b, t_vec2f p);
void						invoke_msg(t_env *d, char *msg);
void						br_msg(t_env *d, t_wall *w, int *n);
void						whi_le(t_env *d, t_sector *sect, int *n,
															double *m);
void						alpha_y(double *sl_y);
void						swap_tabs(short *tab, short *tmp_tab);
void						set_tab(t_env *d, short sect_to_scan,
												short *tab, short old_sect);
int							draw_background(t_env *d, SDL_Event e);
void						draw_message(t_env *d, char *message, int color,
												SDL_Rect rect);
void						draw_wall_nei(t_env *d, t_projdata *p,
												t_frustum *fr);
void						free_sectors_sprites(t_env *d, short i);
void						finish(t_env *d);
double						get_angle(double o, bool is_animated);
double						tan_calculations(double h, double slope,
												t_vec2f p, t_vec2f c);
void						get_sector_center(t_vec2f *v, t_wall *walls,
											int n_walls, int current_wall);
double						calculate_max_floor_h(t_sector *s);
double						*get_screen_pixels();
void						init_keys(Uint8 **keys);
void						v2_rot(t_vec2f *p, double angle);
double						get_floor_height(t_sector *sect, t_wall *walls,
												int16_t sectnum, t_vec2f p);
double						get_ceil_height(t_sector *sect, t_wall *walls,
												int16_t sectnum, t_vec2f p);
t_range						make_range(int min, int max);
t_v2_pair					new_v2_pair(t_vec2f v1, t_vec2f v2);
void						*pure_malloc(size_t size, const char *err);
char						*ft_itoa_static(int n);
double						calculate_floor_height_epsilon(double h);
void						aiming_draw(t_env *d);
int16_t						scan_sect_point_line(t_env *d,
							uint16_t sect_to_scan, double dist, bool hit_all);
double						find_closest_wall_dist(t_env *d,
														uint16_t sect_to_scan);
int16_t						recur_scan_point_line(t_env *d,
						int16_t sect_to_scan, int16_t old_sect, bool hit_all);
double						get_dist_to_intersect_wall(t_env *d,
												t_vec2f wall1, t_vec2f wall2);
void						pixel_put(t_env *d, t_vec3f p, uint32_t color,
																	int mode);
uint32_t					pixel_pls(SDL_Surface *s, double x, double y,
																	int mode);
bool						inside(t_env *d, int16_t sectnum, t_vec2f pos);
bool						clip_wall(double *x1, double *z1, double x2,
																	double z2);
void						proj_wall(t_env *d, t_projdata *p, t_frustum *fr,
																t_vec2f v[2]);
int							new_proj_data(t_projdata *p, t_frustum *fr,
																	int mode);
int							new_proj_data2(t_env *d, t_projdata *p,
													t_frustum *fr, int mode);
void						draw_wall(t_env *d, t_projdata *p, t_frustum *fr);
void						draw_wall_nei(t_env *d, t_projdata *p,
																t_frustum *fr);
void						draw_wall_no_nei(t_env *d, t_projdata *p,
																t_frustum *fr);
void						draw_wall_transparent(t_env *d, t_projdata *p,
																t_frustum *fr);
void						draw_sky(t_env *d, t_projdata *p, t_frustum *fr);
void						draw_ceil_floor(t_env *d, t_projdata *p,
													t_frustum *fr, int mode);
void						player_actions(t_env *d);
void						draw_weapon(t_env *d);
void						blaster_shot(t_env *d);
void						render_sector(t_env *d, t_sector *sect,
																t_frustum *fr);
void						draw_sprite(t_env *d, t_frustum *fr,
														t_sprite_list *sprite);
void						init_player(t_env *d, t_player *player);
void						init_monsters(t_env *d);
void						init_projectiles(t_env *d);
void						swap_list(uint8_t type, uint16_t id, t_env *d,
																int sectnum[2]);
int16_t						update_cursect_smart(t_env *d, short depth,
											t_vec2f pos, uint16_t cursectnum);
int16_t						update_cursect_proj(int16_t sects[2], t_env *d,
														int depth, t_vec3f pos);
void						destroy_mail(short id, t_sector *sector,
													uint8_t type_to_destroy);
void						update_anim_projectile(t_anim_rot *proj,
											t_env *d, short id, bool collided);
void						monster_anim_state(t_monster *monster,
									t_monster_type *monster_type, t_env *d);
void						monster_hit(t_env *d, uint16_t damage,
														uint16_t id_monster);
void						collision_monster_monster(t_env *d, short cur_sect,
															t_monster *monster);
void						collision_with_monster(t_env *d, short cur_sect);
bool						collision_proj_monster(t_env *d, t_sector *sector,
													t_anim_rot *projectile);
bool						collision_proj_player(t_env *d,
													t_anim_rot *projectile);
t_vec3f						trans_v3f_in_scr(t_env *d, t_vec3f v);
void						check_activation(t_env *d, t_monster *monster,
													t_vec2f pos, bool recur);
void						monster_behaviour(t_env *d, t_monster *monster,
																uint16_t id);
void						monster_behaviour_chargingdemon(t_env *d,
											t_monster *monster, uint16_t id);
void						charging_demon_wait(t_monster *monster);
double						shd_fct(t_env *d, t_sector *sector, double dist,
																	int mode);
uint32_t					shade(double factor, uint32_t c);
void						reorder_sprite(t_env *d, t_sector *sect);
t_vec3f						v2_to_v3(t_vec2f v);
t_vec2f						v3_to_v2(t_vec3f v);
double						vec3f_length(t_vec3f v);
bool						is_inside_vec2f(t_vec2f p1, t_vec2f p2,
															t_vec2f point);
bool						is_near(double v1, double v2, double range);
t_vec2f						intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2,
																t_vec2f p3);
uint32_t					alpha(uint32_t	old_colo, uint32_t	new_colo);
void						draw_string(t_env *d, t_font f);
void						init_font(t_env *d);
double						get_floorheight_player(t_env *d, int16_t sectnum);
double						get_floordh(t_env *d, t_sector *sect, t_vec2f v);
double						get_ceilheight_player(t_env *d, int16_t sectnum);
double						get_ceildh(t_env *d, t_sector *sect, t_vec2f v);
void						init_everything(t_env *d, char *map);
void						fix_picnum(t_env *d);
void						handle_finish(t_env *d);
void						play_music(t_env *d, uint8_t id);
void						load_sound(t_env *d, int f);
void						play_sound(t_env *d, uint8_t id, t_vec2f pos);
double						edge_function(t_vec3f a, t_vec3f b, int x, int y);
bool						collision_player(t_env *d, t_sector *sect);
bool						collision_monster(t_env *d, t_sector *sect,
												t_vec2f *pos, double dist_coll);
void						d_asseting(t_env *d, t_projdata *p,
															int16_t sectnum);
void						proj_to_asset(t_env *d, t_projdata *p,
												t_vec3f vect, SDL_Surface *tex);
void						liting_assets(t_env *d, t_projdata *p,
															SDL_Surface *tex);
void						assets_to_draw(t_env *d, t_projdata *p,
														int16_t sectnum, int i);
void						interact_with_assets(t_env *d);
void						use_asset(t_env *d, t_assets *asset);
void						draw_hud(t_env *d);
void						draw_inventory_slot(t_env *d,
											SDL_Surface *tex, int x1, int y1);
void						draw_ammo(t_env *d, t_weapon_type weapon_type);
void						draw_fuel(t_env *d);
void						invoke_msg(t_env *d, char *msg);
bool						door_use(t_env *d, t_sector *sect);
t_vec2f						get_closest(t_vec2f a, t_vec2f b, t_vec2f p);
void						move_monster(t_env *d, int i);
void						draw_health(t_env *d);
void						check_dangerous_area(t_env *d);
void						handle_respawn(t_env *d);
void						precompute_texanim(t_env *d);
void						intro_screen(t_env *d);
int							ft_mod(int i, int n);
void						next_sect_fix(t_env *d);
void						handle_click(t_env *e);
void						pickup_asset(t_env *d);
void						update_2(t_env *d);
bool						validate_argv(char *str);
void						update(t_env *d);
void						player_hit_proj(t_env *d,
													t_anim_rot *projectile);
void						player_fell(t_env *d);
void						contact_with_monster(t_env *d, t_monster *monster);
void						change_buf_colo(t_env *d, uint16_t amount,
																uint32_t colo);
void						color_buffer(t_env *d);
void						change_inertia(t_env *d, double angle,
																double length);
void						inertia(t_env *d, t_vec2f mvt);
void						create_projectile_monster(t_env *d,
									short id_of_proj_type, t_monster *monster);
void						create_projectile(t_env *d, short id_of_proj_type);
uint8_t						get_nb_anim_from_rotation(double monster_rot,
									t_vec2f monster_pos, t_vec2f player_pos);
void						draw_proj(t_env *d, t_frustum *fr,
															t_anim_rot proj);
void						new_disp_data(t_frustum *fr,
								t_display_data *disp_data, uint16_t cursectnum);
void						new_disp_data_1(t_display_data *disp_data,
								SDL_Surface *s, t_vec3f p_in_scr, double size);
void						new_disp_data_2(t_display_data *disp_data,
														uint16_t cursectnum);
void						draw_monster(t_env *d, t_monster monster);
void						disp_sprite(t_env *d, SDL_Surface *s,
									t_display_data disp_data, t_vec2f dist_mod);
void						print_err(const char *err);
void						print_and_quit(t_env *d, const char *str);
void						init_sdl(t_sdl *sdl);
void						loop(t_env *d);
void						event_mouse_motion(t_env *d,
													SDL_MouseMotionEvent event);
void						event_mouse_button(t_env *d,
													SDL_MouseButtonEvent event);
void						event_key_down(t_env *d, SDL_KeyboardEvent event);
void						normal_mode(t_env *d);
void						jump(t_env *d);
void						fly_mode(t_env *d);
void						movement(t_env *d);
void						load_map(t_env *d, char *map);
void						read_posters_data(t_env *d, int f);
void						read_monsters_data(t_env *d, int f);
void						read_assets_texture(t_env *d, int f);
void						read_assets_data(t_env *d, int f);
void						load_monsters_texture(t_env *d, int f);
void						load_weapons_texture(t_env *d, int f, int *nb_tex,
														int *nb_projectiles);
void						loading(t_env *d);
t_vec3f						new_v3_proj(double x, double y);
t_vec3f						new_v3zero();
t_vec3f						new_v3z(double z);
t_vec2f						new_v2zero();
t_range						add_range(t_range a, t_range b);
t_range						minus_range(t_range a, t_range b);
t_range						mult_range(t_range a, t_range b);
t_range						div_range(t_range a, t_range b);
t_vec2						new_v2int(int x, int y);
int							circle(t_env *e, t_vec2 c, int r, Uint32 color);
t_font						new_font(char *str, t_vec2 v, Uint32 color,
																	int scale);
void						print_loading_ascii(t_env *d);
t_vec3f						move_down_vector3(t_vec3f v);
t_vec2						move_down_vector2(t_vec2 v);
void						merge_vector_arr(t_vec3f **a, t_vec3f **b, int ia,
																	int *ib);

#endif
