/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:23:09 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 22:36:19 by vslutiak         ###   ########.fr       */
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

# define N_SECTORS 1024
# define N_WALLS 4096
# define N_MONSTER_TYPES 2
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
	int16_t					n_walls;
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
}							t_sec;

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
	int						objects_n;
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
}							t_objects;

typedef struct				s_monster
{
	t_vec2f					pos;
	t_vec2f					dir;
	double					rot;
	int16_t					this_sect;
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
	uint16_t				this_sect;
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
	bool					visitedportals[N_WALLS];
}							t_frustum;

typedef struct				s_projdata
{
	t_sec					*portal;
	int						ny1a;
	int						ny2a;
	int						ny1b;
	int						ny2b;
	double					u1;
	double					u2;
	double					y_scale;
	t_wall					*wall;
	t_wall					*wall2;
	t_sec					*sector;
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
	t_vec3f					v[3];
	t_vec3f					c[3];
	double					area;
	t_vec3f					a[3];
	t_vec3f					b[3];
	double					z_buff[WIDTH];
	bool					visibility_buf[WIDTH];
	double					door_h;
	double					door_begin;
	double					u1_poster;
	double					u2_poster;
	double					poster_h;
	double					areaa;
	bool					is_on_floor;
	double					shadefactor;
	double					len;
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
	double					scale1;
	double					scale2;
	int						u_tex;
	int						u_poster;
	SDL_Surface				*tex;
	SDL_Surface				*poster;
	int						ya_poster;
	int						yb_poster;
	int						margin;
}							t_proj_env;

# define N_ANIM_PROJ 21
# define COLLISION_ID N_ANIM_PROJ - 1

typedef struct				s_anim_rot
{
	bool					is_active;
	bool					has_collided;
	uint8_t					id_type;
	uint16_t				this_sect;
	t_vec3f					pos;
	t_vec3f					dir;
	uint8_t					weapon_id;
	uint8_t					time_remaining_anim;
	uint8_t					is_curr_anim;
	t_monster				*target;
}							t_anim_rot;

typedef struct				s_proj_type
{
	double					hitbox_radius;
	double					speed;
	double					size;
	uint16_t				damage;
	uint8_t					anim_order[N_ANIM_PROJ];
	uint8_t					kind;
	bool					threat_to_player;
	bool					threat_to_monster;
}							t_anim_rot_type;

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

# define N_WEAPONS 3
# define N_ANIM_WEAPON 15

typedef	struct				s_player
{
	int16_t					health;
	uint8_t					can_be_stomped;
	uint8_t					curr_weap;
	uint8_t					shooting;
	uint8_t					time_new_weapon;
	uint8_t					time_anim_weapon;
	uint8_t					is_curr_anim;
	uint8_t					anim_speed[N_WEAPONS];
	uint8_t					anim_weap[N_WEAPONS][N_ANIM_WEAPON];
	uint8_t					click;
	uint16_t				flying;
	uint8_t					moving;
	double					min_h;
	double					gravity;
}							t_player;

# define MAX_BUF_VALUE 240

typedef struct				s_pxls
{
	uint32_t				colo;
	int16_t					value;
}							t_pxls;

# define MAXNBOFANIMATION 5
# define N_ANIM_ROTS_WEAPON N_ANIM_PROJ
# define N_ANIM_ROT_TYPES 3
# define N_ANIM_ROTS 100
# define MOUSE_PRESSED 1
# define MOUSE_RELEASED 2
# define MOUSE_NO_ACTION 3
# define N_SOUNDS 20

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
	SDL_Surface				*monster_text[N_MONSTER_TYPES]
	[MAX_STATE_MONSTER][MAXNBOFANIMATION];
	SDL_Surface				*anim_rot_text[N_ANIM_ROT_TYPES]
	[N_ANIM_ROTS_WEAPON];
	SDL_Surface				*weapon_tex[N_WEAPONS]
	[N_ANIM_WEAPON];
	Uint8					*keys;
	uint8_t					left_mouse_button;
	uint8_t					right_mouse_button;
	t_cam					startcam;
	t_cam					cam;
	t_sec					sectors[N_SECTORS];
	t_wall					walls[N_WALLS];
	t_monster				*monsters;
	t_objects				**objects;
	int16_t					objects_n;
	t_monster_type			monster_type[N_MONSTER_TYPES];
	t_anim_rot				anim_rots[N_ANIM_ROTS];
	t_anim_rot_type			anim_rot_type[N_ANIM_ROT_TYPES];
	t_weapon_type			weapon_type;
	uint16_t				monst_n;
	int16_t					n_sect;
	int16_t					n_walls;
	int16_t					sect_begin;
	int16_t					this_sect;
	bool					debug_pause;
	double					anim_door[N_WALLS];
	double					door_active[N_WALLS];
	double					sparks;
	t_pxls					pxls;
	t_vec2f					inertia;
	unsigned char			font[96][5];
	int						used[96];
	double					*z_buff;
	double					player_floor_h;
	double					player_ceil_h;
	char					nextmap[100];
	Mix_Chunk				*chunk[N_SOUNDS];
	t_objects				*slot2;
	t_objects				*slot3;
	char					msg[100];
	uint32_t				msg_start;
	uint32_t				harmful_area;
	int						hard;
	t_chars					chars;
	int						loaded;
	TTF_Font				*g_font;
	unsigned int			tick;
	void					*vslutiak;
}							t_env;

typedef struct				s_thread_arg
{
	t_env					*d;
	t_proj_env				*p;
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

# define MOUSE_SENSITIVTY 1

# define MINIMUM_HEIGHT 0.5

# define MAX_INERTIA 0.19

# define SPEED_ANIM 10
# define SPEED_ANIM_CHARG 7
# define SPEED_ANIM_CHOW 17
# define MOTHER_DEMON_ATTACK 6

# define BOUNCING_DIST_PROJ 0.12
# define BOUNCING_DIST_MOTHERDEMON 0.1

# define MIN_DIST_TO_PLAYER 0.15

# define NB_OF_SECTOR_DEPTH 2

# define SLOT_W 64

# define NB_TEX (int[3]){13, 15, 3}
# define NB_PROJECTILE (int[3]){20, 0, 5}

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
# define MAX_CHANNELS 100
# define MINIMUM_CROUCH_HEIGHT 0.2
# define MINIMUM_CEIL_DIST 0.1
# define JUMP_FIX 0.01
# define JUMP_FORCE 0.08
# define RED 0xFF0000
# define GREEN_BLAST 0x5CE26E
# define HEALTH_COLO 0xFFFF66
# define SAME_POS(v1, v2) (((v1.x) == (v2.x)) && ((v1.y) == (v2.y)))
# define F_ANIM 1
# define PICKUP_RANGE 2

void						buf_to_collor2(t_env *d, uint16_t amount,
															uint32_t colo);
double						distanse_place(t_vec2f a, t_vec2f b, t_vec2f p);
void						massege_print(t_env *d, char *msg);
void						door_func(t_env *d, t_sec *sect, int *n,
															double *m);
void						alpha_serch(double *sl_y);
void						tabulation_sw(short *tab, short *tmp_tab);
void						tab_new(t_env *d, short sect_to_scan,
												short *tab, short old_sect);
int							displaing_backgr(t_env *d, SDL_Event e);
void						displaing_msg(t_env *d, char *message, int color,
												SDL_Rect rect);
void						displaing_n_wall(t_env *d, t_proj_env *p,
												t_frustum *fr);
void						del_mem_spr(t_env *d, short i);
void						ending(t_env *d);
double						angles_val(double o, bool is_animated);
double						angle_caluk_tang(double h, double slope,
												t_vec2f p, t_vec2f c);
void						mid_sect_val(t_vec2f *v, t_wall *walls,
											int n_walls, int current_wall);
double						height_calc_fl(t_sec *s);
double						*pix_val_scr();
void						keyboard_battons(Uint8 **keys);
void						rotation_vector(t_vec2f *p, double angle);
double						height_fl_val(t_sec *sect, t_wall *walls,
												int16_t sectnum, t_vec2f p);
double						height_cl_val(t_sec *sect, t_wall *walls,
												int16_t sectnum, t_vec2f p);
t_range						ranged_create(int min, int max);
t_v2_pair					new_v2_pair(t_vec2f v1, t_vec2f v2);
void						*pure_malloc(size_t size, const char *err);
char						*new_itoa_fun(int n);
double						height_calc_fl_eps(double h);
void						displaing_aiming(t_env *d);
double						get_dist_to_intersect_wall(t_env *d,
												t_vec2f wall1, t_vec2f wall2);
void						pixel_put(t_env *d, t_vec3f p, uint32_t color,
																	int mode);
uint32_t					pixel_pls(SDL_Surface *s, double x, double y,
																	int mode);
bool						to_wall_lock(double *x1, double *z1, double x2,
																	double z2);
void						proj_wall(t_env *d, t_proj_env *p, t_frustum *fr,
																t_vec2f v[2]);
int							new_proj_data(t_proj_env *p, t_frustum *fr,
																	int mode);
int							new_proj_data2(t_env *d, t_proj_env *p,
													t_frustum *fr, int mode);
void						displaing_wall(t_env *d, t_proj_env *p,
																t_frustum *fr);
void						displaing_no_n_wall(t_env *d, t_proj_env *p,
																t_frustum *fr);
void						displaing_to_transp_wall(t_env *d, t_proj_env *p,
																t_frustum *fr);
void						displaing_sky(t_env *d, t_proj_env *p,
																t_frustum *fr);
void						displaing_cl_fl(t_env *d, t_proj_env *p,
													t_frustum *fr, int mode);
void						actio_pl(t_env *d);
void						displaing_weap(t_env *d);
void						sect_rendering(t_env *d, t_sec *sect,
																t_frustum *fr);
void						dislaing_not_wall(t_env *d, t_frustum *fr,
														t_sprite_list *sprite);
void						play_initialization(t_env *d, t_player *player);
void						monters_inicialization(t_env *d);
void						init_monster_type(t_env *d);
void						init_monster_type_2(t_env *d);
void						proj_initialization(t_env *d);
void						list_swp(uint8_t type, uint16_t id, t_env *d,
																int sectnum[2]);
int16_t						new_smart_curs(t_env *d, short depth,
											t_vec2f pos, uint16_t this_sect);
int16_t						new_proj_curs(int16_t sects[2], t_env *d,
														int depth, t_vec3f pos);
void						mailing_deleted(short id, t_sec *sector,
													uint8_t type_to_destroy);
void						new_proj_animate(t_anim_rot *proj,
											t_env *d, short id, bool collided);
void						monst_st_animate(t_monster *monster,
									t_monster_type *monster_type, t_env *d);
void						monst_by_monst_colided(t_env *d, short cur_sect,
															t_monster *monster);
void						play_by_monst_colided(t_env *d, short cur_sect);
bool						proj_monst_colided(t_env *d, t_sec *sector,
													t_anim_rot *projectile);
bool						proj_play_colided(t_env *d,
													t_anim_rot *projectile);
t_vec3f						v3f_transpar(t_env *d, t_vec3f v);
void						activate_tring(t_env *d, t_monster *monster,
													t_vec2f pos, bool recur);
void						demeanor_monst(t_env *d, t_monster *monster,
																uint16_t id);
void						demeanor_char_demyon(t_env *d,
											t_monster *monster, uint16_t id);
void						dellay_char_demyon(t_monster *monster);
double						shd_fct(t_env *d, t_sec *sector, double dist,
																	int mode);
uint32_t					shad(double factor, uint32_t c);
void						reorder_sprite(t_env *d, t_sec *sect);
t_vec3f						v2_to_v3(t_vec2f v);
t_vec2f						v3_to_v2(t_vec3f v);
double						vec3f_length(t_vec3f v);
bool						is_inside_vec2f(t_vec2f p1, t_vec2f p2,
															t_vec2f point);
uint32_t					to_search_alpha(uint32_t	old_colo,
														uint32_t	new_colo);
void						displaing_str(t_env *d, t_font f);
void						font_initialize(t_env *d);
double						height_play_fl_val(t_env *d, int16_t sectnum);
double						fl_calc_vec_cal(t_env *d, t_sec *sect,
																t_vec2f v);
double						height_play_cl_val(t_env *d, int16_t sectnum);
double						cl_calc_vec_cal(t_env *d, t_sec *sect,
																t_vec2f v);
void						to_load_numbpic(t_env *d);
void						ending_hd(t_env *d);
void						music_player(t_env *d, uint8_t id);
void						music_loader(t_env *d, int f);
void						play_sound(t_env *d, uint8_t id, t_vec2f pos);
double						fun_to_edget(t_vec3f a, t_vec3f b, int x, int y);
bool						collision_player(t_env *d, t_sec *sect);
bool						collision_monster(t_env *d, t_sec *sect,
												t_vec2f *pos, double dist_coll);
void						d_asseting(t_env *d, t_proj_env *p,
															int16_t sectnum);
void						proj_to_asset(t_env *d, t_proj_env *p,
												t_vec3f vect, SDL_Surface *tex);
void						to_liet_assets(t_env *d, t_proj_env *p,
															SDL_Surface *tex);
void						assets_to_interactive(t_env *d);
void						use_asset(t_env *d, t_objects *asset);
void						displaing_huds(t_env *d);
void						displaing_invent(t_env *d,
											SDL_Surface *tex, int x1, int y1);
void						displaing_ammo(t_env *d, t_weapon_type weapon_type);
void						displaing_fuel(t_env *d);
bool						door_use(t_env *d, t_sec *sect);
t_vec2f						to_close_val(t_vec2f a, t_vec2f b, t_vec2f p);
void						view_danget_stash(t_env *d);
void						respauning_h(t_env *d);
void						texture_pre_anim(t_env *d);
void						to_sector_load(t_env *d);
void						check_pressed(t_env *e);
void						reloade_2(t_env *d);
bool						check_inp_par(char *str);
void						reloade(t_env *d);
void						proj_to_hit_play(t_env *d,
													t_anim_rot *projectile);
void						play_active(t_env *d);
void						play_and_monst_acive(t_env *d, t_monster *monster);
void						buf_to_collor1(t_env *d);
void						to_ch_iter(t_env *d, double angle,
																double length);
void						to_iner(t_env *d, t_vec2f mvt);
void						proj_monst_creat(t_env *d,
									short id_of_proj_type, t_monster *monster);
void						to_proj_creat(t_env *d, short id_of_proj_type);
uint8_t						get_nb_anim_from_rotation(double monster_rot,
									t_vec2f monster_pos, t_vec2f player_pos);
void						display_proj(t_env *d, t_frustum *fr,
															t_anim_rot proj);
void						replace_data_to_disp(t_frustum *fr,
								t_display_data *disp_data, uint16_t this_sect);
void						replace_data_to_disp_1(t_display_data *disp_data,
								SDL_Surface *s, t_vec3f p_in_scr, double size);
void						replace_data_to_disp_2(t_display_data *disp_data,
														uint16_t this_sect);
void						displaing_monst(t_env *d, t_monster monster);
void						displaing_sprite(t_env *d, SDL_Surface *s,
									t_display_data disp_data, t_vec2f dist_mod);
void						print_err(const char *err);
void						print_and_quit(t_env *d, const char *str);
void						sdl_inicialization(t_sdl *sdl);
void						loop(t_env *d);
void						ev_mot_mouse(t_env *d,
													SDL_MouseMotionEvent event);
void						ev_butt_mouse(t_env *d,
													SDL_MouseButtonEvent event);
void						ev_keydown(t_env *d, SDL_KeyboardEvent event);
void						normal_mode(t_env *d);
void						jumping(t_env *d);
void						fly_mode(t_env *d);
void						to_move_func(t_env *d);
void						to_loading_map(t_env *d, char *map);
void						loading_data_post(t_env *d, int f);
void						loading_data_monst(t_env *d, int f);
void						loading_asset_text(t_env *d, int f);
void						loading_data_asset(t_env *d, int f);
void						loading_text_monst(t_env *d, int f);
void						loading_text_weap(t_env *d, int f, int *nb_tex,
														int *nb_projectiles);
void						to_load(t_env *d);
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
void						translate(t_vec3f *p, t_vec3f move, int dir);
void						rot_x(t_vec3f *v, double ang, t_vec3f axis);
void						rot_y(t_vec3f *v, double ang, t_vec3f axis);
void						rot_z(t_vec3f *v, double ang, t_vec3f axis);
void						read_texture_data(t_env *d, int f);
t_vec3f						transform_back(t_env *d, t_vec3f v);
t_sec						*check_neighbor(t_env *d, int16_t nei);
t_vec3f						transform_back(t_env *d, t_vec3f v);
void						draw_char(t_env *d, t_font f);
void						draw_bitmap(t_env *d, t_bitmap bitmap, int x,
																	int y);
void						dm_exit(t_env *d, int active_option, int c);
void						month_ini(double rand, t_vec2f tmp, t_vec2f tmp2,
	t_monster *monster);
t_vec3f						transform_back(t_env *d, t_vec3f v);
t_sec						*check_neighbor(t_env *d, int16_t nei);
void						swap_vals(double *a, double *b);
double						get_smh(t_vec3f v1, t_vec3f v2);
void						change_list(t_sprite_list *one, t_sprite_list *two,
	t_sprite_list *prev);
void						skip(void *smh);
int16_t						second_sin(t_env *env, short k);
void						third_sin(t_env *env, short k);
void						fourth_sin(t_env *env, short k);
void						fifth_sin(t_env *env, short *k);
#endif
