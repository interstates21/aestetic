#ifndef COMMON_H
# define COMMON_H

#include "../frameworks/SDL2/SDL.h"
#include "../frameworks/SDL2/SDL_render.h"
#include "../libft/libft.h"

#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

# include <stdbool.h>


// typedef enum
// {
// 	false,
// 	true
// } bool;


#define CLAMP(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))

# define MAXNUMSECTORS 1024
# define MAXNUMMONSTERS 256
# define MAXNUMWALLS 4096
# define MAXTYPEMONSTERS 2

typedef struct				s_font
{
	char					*str;
	int						x;
	int						y;
	uint32_t				color;
	int						scale;
}							t_font;

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
# define BLASTER 1
# define M16 2
# define FIREBALL_1 1

typedef struct				s_sprite_list
{
	int16_t					id;
	struct s_sprite_list	*next;
	uint8_t					type;
}							t_sprite_list;

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
	int16_t					blaster_ammo;
	int16_t					m16_ammo;
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

# define MOTHERDEMON 0
# define CHARGINGDEMON 1

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

typedef struct				s_texture_data
{
	char					name[100];
	int						used;
	struct s_texture_data	*begin;
	struct s_texture_data	*prev;
	struct s_texture_data	*next;
}							t_texture_data;

/*
** vec2.c
*/

t_vec2f						v2_min(t_vec2f v1, t_vec2f v2);
t_vec2f						v2_plus(t_vec2f v1, t_vec2f v2);
void						actualize_dir(double angle, t_vec2f *vec);
t_vec3f						v3_min(t_vec3f v1, t_vec3f v2);
t_vec3f						v3_scale(t_vec3f v1, double scalar);

/*
** vec2_2.c
*/

t_vec2f						v2_scale(t_vec2f v, double scalar);
float						v2_dot(t_vec2f v);
double						v2_len(t_vec2f v);
double						v2_atan(t_vec2f v1, t_vec2f v2);
t_vec3f						v3_plus(t_vec3f a, t_vec3f b);

#endif
