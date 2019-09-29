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
#ifdef APPLE
#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
#elif linux
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


#endif

#include "macros.h"

#define MAP_WIDTH 5
#define MAP_HEIGHT 6
#define UNDEF -42
#define INFIN 100000
#define WIDTH 800
#define HEIGHT 600
#define EYE_HEIGHT 6
#define DUCK_HEIGHT 2.5
#define HEAD_MARGIN 1
#define KNEE_HIGHT 2
#define MAX_Q		32

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
	int n_sector;
	int sx;
	int sy;
} t_queue;

typedef struct s_v2f
{
	double x;
	double y;
	// double z;
} t_v2f;

typedef struct s_cam
{
	double hfov;
	double vfov;
	t_vt camSpace1;
	t_vt camSpace2;
	double	n_z;
	double	f_z;
	double	n_s;
	double	f_s;
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

typedef struct	s_player
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
	bool rot_left;
	bool rot_right;
	bool squat;
	float yaw;
	bool jumping;
	bool ducking;
	bool moving;
	bool ground;
	bool rotating;
	bool falling;
	t_v2i mouse;

} t_controller;

/*
 * floor  = высота пола
 *  ceil  = высота потолка
 *  *walls  = х, у координаты вершин
 *  *portals = указатель на соседний сектор
 * npoints  = кол-во вершин
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

typedef struct	s_line
{
	int			light;
	t_v2i		pos;
	int			x;
}				t_line;

typedef struct	s_math
{
	t_v2f		v1;
	t_v2f		v2;
	t_v2f		scale[2];
	int			x[2];
	t_v2i		rot[2];
	t_v2i		prot[2];
}				t_math;

typedef struct	s_draw
{
	t_player	player;
	t_queue		queue[MAX_Q];
	t_queue		cur;
	t_sector	*sec;
	int			head;
	int			tail;
	int			top[WIDTH];
	int			bot[WIDTH];
	int			*flags;
	t_v2i		range;
	int			portal;
}				t_draw;

typedef struct	s_scheme
{
	int			x;
	int			y1;
	int			y2;
	int			top;
	int			mid;
	int			bot;
}				t_scheme;

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