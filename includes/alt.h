#ifndef DOOM_H
#define DOOM_H

#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../frameworks/SDL2/SDL.h"
#include "../frameworks/SDL2/SDL_render.h"
#include "../libft/libft.h"
#include "bisquit.h"
#ifdef __APPLE__
#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
#elif __linux__
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#endif

#include "macros.h"

#define MAP_WIDTH 5
#define MAP_HEIGHT 6
#define WIDTH 800
#define HEIGHT 600
#define EYE_HEIGHT 6
#define DUCK_HEIGHT 2.5
#define HEAD_MARGIN 1
#define KNEE_HIGHT 2
#define H_FOV (0.73f * HEIGHT)
#define V_FOW (.2f * HEIGHT)

typedef enum
{
	false,
	true
} bool;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
	int a;
} t_rgb;

typedef struct s_vt
{
	double x;
	double y;
	double z;
} t_vt;

typedef struct s_queue
{
	int nSector;
	int	sx;
	int sy;
} t_queue;


typedef struct s_v2f
{
	double x;
	double y;
	double z;
} t_v2f;

typedef struct s_cam
{
	double hfov;
	double vfov;
	t_vt camSpace1;
	t_vt camSpace2;

} t_cam;

typedef struct s_v2i
{
	int x;
	int y;
} t_v2i;

typedef struct s_range_i
{
	int min;
	int max;
} t_range;

typedef struct s_player
{
	t_vt pos;
	t_vt dir;
	double angle;
	double anglesin;
	double anglecos;
	double yaw;
	double move_speed;
	double rot_speed;
	bool falling;
	unsigned int sector;
} t_player;

typedef struct s_controller
{
	bool move_forw;
	bool move_back;
	bool move_left;
	bool move_right;
	bool squat;
	bool jumping;
	bool rotating;
	bool checkmouse_way;
	bool falling;
	t_v2i mouse;

} t_controller;

/*
 *	floor		= высота пола
 * 	ceil		= высота потолка
 * 	*walls		= х, у координаты вершин
 * 	*neighbours	= указатель на соседний сектор
 *	npoints		= кол-во вершин
 */
typedef struct s_sector
{
	double floor;
	double ceil;
	t_vt *walls;
	char *portals;
	unsigned int npoints;
} t_sector;
/**/

typedef struct s_scene
{
	Uint32 *pixels;
	Uint32 **textures;
	t_player player;
	t_controller controller;
	t_cam cam;
	char **map;
	int tex_height;
	int tex_width;
	int map_width;
	int map_height;
	int n_sectors;
	t_sector *sectors;
} t_scene;

typedef struct s_sdl
{
	SDL_Window *window;
	SDL_Surface *surface_sreen;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	/* not used */
	SDL_Surface *surface;
	//
	SDL_Event event;
} t_sdl;

#include "functions.h"

#endif
