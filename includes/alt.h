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
# define EYE_HEIGHT		6
# define DUCK_HEIGHT	2.5
# define HEAD_MARGIN	1
# define KNEE_HIGHT		2
# define H_FOV			(0.73 * HEIGHT)
# define V_FOV			(0.2 * HEIGHT)
# define MAX_Q			32
# define N_Z			0.0001
# define F_Z			5
# define N_SIDE			0.00001
# define F_SIDE			20.0

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

typedef struct s_v2f
{
	double x;
	double y;
} t_v2f;

typedef struct s_v3f
{
	double x;
	double y;
	double z;
} t_v3f;


typedef struct s_v2
{
	int x;
	int y;
} t_v2;

typedef struct		s_player
{
	t_v3f			pos;
	t_v3f			motion;
    double			angle;
	double			anglesin;
	double			anglecos;
	double			yaw;
	double			move_speed;
	double			rot_speed;
	unsigned int	sector;
}					t_player;

typedef struct	s_controller
{
	bool		move_forw;
	bool		move_back;
	bool		rot_left;
	bool		rot_right;
	bool		ground;
	bool		falling;
	bool		moving;
	bool		ducking;


	//to remove
	float		yaw;
	int			mouse_x;
	int			mouse_y;
	bool		checkmouse_way;
}				t_controller;

/*
 *	floor		= высота пола
 * 	ceil		= высота потолка
 * 	*vertex		= х, у координаты вершин
 * 	*neighbours	= указатель на соседний сектор
 *	npoints		= кол-во вершин
 */
typedef struct		s_sector
{
	double			floor;
	double			ceil;
	t_v2f			*vertex;
	/*signed*/ char	*portals;
	unsigned int	npoints;
}					t_sector;
/**/

typedef struct		s_line
{
	int				x;
	int 			y1;
	int 			y2;
	int 			c_top;
	int 			c_mid;
	int 			c_bot;
}					t_line;

typedef struct		s_math
{
	t_v2f			v1;
	t_v2f			v2;
	t_v2f			t1;
	t_v2f			t2;
	double			pcos;
	double			psin;
	t_v2f			in1;
	t_v2f			in2;
	t_v2f			scale1;
	t_v2f			scale2;
	int				x1;
	int 			x2;
	double			y_ceil;
	double			y_floor;
	int 			nghbr;
	double			nyceil;
	double			nyfloor;
	t_v2			y1;
	t_v2			y2;
	t_v2			ny1;
	t_v2			ny2;
	int				begin;
	int 			end;
}					t_math;

typedef struct		s_item
{
	int				sector_n;
	int 			sx1;
	int 			sx2;
}					t_item;

typedef struct		s_draw
{
	t_item			queue[MAX_Q];
	t_item			*head;
	t_item			*tail;
	t_item			now;
	int 			ytop[WIDTH];
	int 			ybot[WIDTH];
	int 			*render_sec;
	t_sector		*sec;
	int				z;
	int				ya;
	int				yb;
}					t_draw;

typedef struct		s_scene
{
	Uint32			*pixels;
	Uint32			**textures;
	t_player		player;
	t_controller	controller;
	char			**map;
	int				tex_height;
	int				tex_width;
	int				map_width;
	int				map_height;
	int				n_sectors;
	t_sector		*sectors;
}					t_scene;



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
