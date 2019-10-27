#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <stdbool.h>
# include "common.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <limits.h>
# define WIDTH 800
# define HEIGHT 600
# define MUST_BE_DESTROYED 255
# define FPS 60
# define MAX_Y_OFFSET (HEIGHT/2)
# define PLAYER_HITBOX 0.1
# include "structs_doom.h"
# include "defines.h"
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

void	change_buf_colo(t_data *d, uint16_t amount, uint32_t colo);
double	get_dist(t_vec2f a, t_vec2f b, t_vec2f p);
void	invoke_msg(t_data *d, char *msg);
void	br_msg(t_data *d, t_wall *w, int *n);
void	whi_le(t_data *d, t_sector *sect, int *n, double *m);
void	alpha_y(double *sl_y);
void	swap_tabs(short *tab, short *tmp_tab);
void	set_tab(t_data *d, short sect_to_scan, short *tab, short old_sect);
int		draw_background(t_data *d, SDL_Event e);
void 	draw_message(t_data *d, char *message, int color, SDL_Rect rect);



double get_angle(double o, bool isAnimated);
double tan_calculations(double h, double slope, t_vec2f p, t_vec2f c);
void	get_sector_center(t_vec2f *v, t_wall *walls, int nWalls, int currentWall);
double calculate_max_floor_h(t_sector *s);
double *get_screen_pixels();
void	init_keys(Uint8 **keys);
void	v2_rot(t_vec2f *p, double angle);
double	get_floor_height(t_sector *sect, t_wall *walls, int16_t sectnum, t_vec2f p);
double	get_ceil_height(t_sector *sect, t_wall *walls, int16_t sectnum, t_vec2f p);
t_range   make_range(int min, int max);
t_v2_pair new_v2_pair(t_vec2f v1, t_vec2f v2);
void *pure_malloc(size_t size, const char *err);


char	*ft_itoa_static(int n);

double 		calculate_floor_height_epsilon(double h);
void		aiming_draw(t_data *d);
int16_t		scan_sect_point_line(t_data *d, uint16_t sect_to_scan, double dist,
		bool hit_all);
double		find_closest_wall_dist(t_data *d, uint16_t sect_to_scan);
int16_t		recur_scan_point_line(t_data *d,
		int16_t sect_to_scan, int16_t old_sect, bool hit_all);
double		get_dist_to_intersect_wall(t_data *d, t_vec2f wall1, t_vec2f wall2);
void		pixel_put(t_data *d, t_vec3f p, uint32_t color, int mode);
uint32_t	pixel_pls(SDL_Surface *s, double x, double y, int mode);
bool		inside(t_data *d, int16_t sectnum, t_vec2f pos);
bool		clip_wall(double *x1, double *z1, double x2, double z2);
void		proj_wall(t_data *d, t_projdata *p, t_frustum *fr, t_vec2f v[2]);
int			new_proj_data(t_projdata *p, t_frustum *fr, int mode);
int			new_proj_data2(t_data *d, t_projdata *p, t_frustum *fr, int mode);
void		drawing_wall(t_vec2 y_value, t_data *d, t_projdata *p, int mode);
void		draw_wall(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_wall_no_nei(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_wall3(t_data *d, t_projdata *p, t_frustum *nfr, bool *visible);
void		draw_wall_transparent(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_sky(t_data *d, t_projdata *p, t_frustum *fr);//bdeomin
void		draw_ceil_floor(t_data *d, t_projdata *p, t_frustum *fr, int mode);//bdeomin
void		player_actions(t_data *d);
void		draw_weapon(t_data *d);
void		blaster_shot(t_data *d);
void		render_sector(t_data *d, t_sector *sect, t_frustum *fr);
void		draw_sprite(t_data *d, t_frustum *fr, t_sprite_list *sprite);
void		init_player(t_data *d, t_player *player);
void		init_monsters(t_data *d);
void		init_projectiles(t_data *d);
void		swap_list(uint8_t type, uint16_t id, t_data *d, int sectnum[2]);
int16_t		update_cursect_smart(t_data *d,
		short depth, t_vec2f pos, uint16_t cursectnum);
int16_t		update_cursect_proj(int16_t sects[2],
		t_data *d, int depth, t_vec3f pos);
void		destroy_mail(short id, t_sector *sector, uint8_t type_to_destroy);
void		update_anim_projectile(t_projectile *proj, t_data *d, short id,
			bool collided);
void		monster_anim_state(t_monster *monster,
		t_monster_type *monster_type, t_data *d);
void		monster_hit(t_data *d, uint16_t damage, uint16_t id_monster);
void		collision_monster_monster(t_data *d,
		short cur_sect, t_monster *monster);
void		collision_with_monster(t_data *d, short cur_sect);
bool		collision_proj_monster(t_data *d,
		t_sector *sector, t_projectile *projectile);
bool		collision_proj_player(t_data *d, t_projectile *projectile);
t_vec3f		trans_v3f_in_scr(t_data *d, t_vec3f v);
void		check_activation(t_data *d, t_monster *monster, t_vec2f pos,
		bool recur);
void		monster_behaviour(t_data *d, t_monster *monster, uint16_t id);
void		monster_behaviour_chargingdemon(
		t_data *d, t_monster *monster, uint16_t id);
void		charging_demon_wait(t_monster *monster);
double		shd_fct(t_data *d, t_sector *sector, double dist, int mode);
uint32_t	shade(double factor, uint32_t c);
void		reorder_sprite(t_data *d, t_sector *sect);
t_vec3f		v2_to_v3(t_vec2f v);
t_vec2f		v3_to_v2(t_vec3f v);
double		vec3f_length(t_vec3f v);
bool		is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point);
bool		is_near(double v1, double v2, double range);

t_vec2f		intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2, t_vec2f p3);
uint32_t	alpha(uint32_t	old_colo, uint32_t	new_colo);
void		draw_string(t_data *d, t_font f);
void		init_font(t_data *d);
double		get_floorheight_player(t_data *d, int16_t sectnum);
double		get_floordh(t_data *d, t_sector *sect, t_vec2f v);
double		get_ceilheight_player(t_data *d, int16_t sectnum);
double		get_ceildh(t_data *d, t_sector *sect, t_vec2f v);
void		init_everything(t_data *d, char *map);
void		fix_picnum(t_data *d);
void		handle_finish(t_data *d);
void		play_music(t_data *d, uint8_t id);
void		load_sound(t_data *d, int f);
void		play_sound(t_data *d, uint8_t id, t_vec2f pos);
double		edge_function(t_vec3f a, t_vec3f b, int x, int y);//bdeomin
bool		collision_player(t_data *d, t_sector *sect);//bdeomin
bool		collision_monster(t_data *d,
		t_sector *sect, t_vec2f *pos, double dist_coll);//bdeomin
void		d_asseting(t_data *d,
		t_projdata *p, int16_t sectnum);//bdeomin
void		proj_to_asset(t_data *d, t_projdata *p, t_vec3f vect, SDL_Surface *tex);//bdeomin
void		liting_assets(t_data *d, t_projdata *p, SDL_Surface *tex);//bdeomin
void		assets_to_draw(t_data *d, t_projdata *p, int16_t sectnum, int i);//bdeomin
void		interact_with_assets(t_data *d);//bdeomin
void		use_asset(t_data *d, t_assets *asset);//bdeomin
void		draw_hud(t_data *d);//bdeomin
void		draw_inventory_slot(t_data *d, SDL_Surface *tex, int x1, int y1);//bdeomin
void		draw_ammo(t_data *d, t_weapon_type weapon_type);//bdeomin
void		draw_fuel(t_data *d);//bdeomin
void		invoke_msg(t_data *d, char *msg);
bool		door_use(t_data *d, t_sector *sect);
t_vec2f		get_closest(t_vec2f a, t_vec2f b, t_vec2f p);
void		move_monster(t_data *d, int i);
void		draw_health(t_data *d);
void		check_dangerous_area(t_data *d);
void		handle_respawn(t_data *d);
void		precompute_texanim(t_data *d);
void		intro_screen(t_data *d);
int			ft_mod(int i, int n);
void		next_sect_fix(t_data *d);
void		handle_click(t_data *e);
void 		pickup_asset(t_data *d);

/*
** update_2.c
*/

void		update_2(t_data *d);


bool		validate_argv(char *str);
/*
** update.c
*/

void		update(t_data *d);

/*
** player_damage.c
*/
void		player_hit_proj(t_data *d, t_projectile *projectile);
void		player_fell(t_data *d);
void		contact_with_monster(t_data *d, t_monster *monster);
/*
** color_buffer.c
*/
void		change_buf_colo(t_data *d, uint16_t amount, uint32_t colo);
void		color_buffer(t_data *d);
/*
** inertia.c
*/
void		change_inertia(t_data *d, double angle, double length);
void		inertia(t_data *d, t_vec2f mvt);
/*
** create_projectile.c
*/

void		create_projectile_monster(
		t_data *d, short id_of_proj_type, t_monster *monster);
void		create_projectile(t_data *d, short id_of_proj_type);

/*
** get_rot_monster.c
*/

uint8_t		get_nb_anim_from_rotation(double monster_rot,
		t_vec2f monster_pos, t_vec2f player_pos);
/*
** fly_gravity.c
*/

void		fly_gravity(t_data *d);

/*
** draw_monster.c
*/

void		draw_monster(t_data *d, t_monster monster);
void		disp_sprite(t_data *d, SDL_Surface *s,
					t_display_data disp_data, t_vec2f dist_mod);
void		new_zbuffer_and_put_collor(t_data *d, t_vec2 x_y, uint32_t colo,
															t_vec2f dist_mod);

/*
** exit.c
*/

void	print_err(const char *err);
void	print_and_quit(t_data *d, const char *str);

/*
** ini
*/

void		init_sdl(t_sdl *sdl);

/*
** loop.c
*/

void		loop(t_data *d);

/*
** events.c
*/

void		event_mouse_motion(t_data *d, SDL_MouseMotionEvent event);
void		event_mouse_button(t_data *d, SDL_MouseButtonEvent event);
void		event_key_down(t_data *d, SDL_KeyboardEvent event);

/*
** jump.c
*/

void		normal_gravity(t_data *d);
void		jump(t_data *d);

/*
**	movement.c
*/

void		movement(t_data *d);

/*
**	load_map.c
*/

void		load_map(t_data *d, char *map);

/*
**	load_assets.c
*/

void		read_posters_data(t_data *d, int f);
void		read_monsters_data(t_data *d, int f);
void		read_assets_texture(t_data *d, int f);
void		read_assets_data(t_data *d, int f);

void		load_monsters_texture(t_data *d, int f);

void		load_weapons_texture(t_data *d,
		int f, int *nb_tex, int *nb_projectiles);
void		loading(t_data *d);

t_vec3f		new_v3_projection(double x, double y);
t_vec3f		new_v3zero();
t_vec3f		new_v3z(double z);
t_vec2f		new_v2zero();
t_range		add_range(t_range a, t_range b);
t_range		minus_range(t_range a, t_range b);
t_range		mult_range(t_range a, t_range b);
t_range		div_range(t_range a, t_range b);
t_vec2		new_v2int(int x, int y);
int			circle(t_data *e, t_vec2 c, int r, Uint32 color);
t_font		new_font(char *str, t_vec2 v, Uint32 color, int scale);
void      	print_loading_ascii(t_data *d);
t_vec3f		move_down_vector3(t_vec3f v);
t_vec2		move_down_vector2(t_vec2 v);

#endif
