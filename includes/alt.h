#ifndef DOOM_H
#define DOOM_H

#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "libft.h"
#ifdef __APPLE__
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#elif __linux__
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#endif

#include "macros.h"

#define MAP_WIDTH 5
#define MAP_HEIGHT 6
#define WIDTH 1200
#define HEIGHT 600

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

typedef struct s_v2
{
	int x;
	int y;
} t_v2;

typedef struct s_player
{
	t_v2f pos;
	t_v2f dir;
	t_v2f view;
	double move_speed;
	double rot_speed;
	bool move_forw;
	bool move_back;
	bool rot_left;
	bool rot_right;
} t_player;

typedef struct s_ray
{
	t_v2f dir;
	t_v2 move_side;
	t_v2 cell;
	t_v2f dist;
	t_v2f dist_delta;
	char hit_side;
	bool is_hit;
	double dist_hit;
	int line_height;
} t_ray;

typedef struct s_scene
{
	Uint32 *pixels;
	Uint32 **textures;
	char **map;
	int tex_height;
	int tex_width;
	int map_width;
	int map_height;
	t_player player;

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
