

#ifndef DOOM_H
# define DOOM_H

# include <time.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include "libft.h"

#ifdef __APPLE__
# include "SDL2.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
#elif __linux__
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>
#endif

# define WIDTH 1280
# define HEIGHT 1000
# define THREADS 8
# define TEXTURENUM 16
# define TRUE 1

# define IS_WALL(n)(n & 0xFFFFL)
# define TOP_WALL(n)((n & 0xFL) - 1)
# define BOT_WALL(n)(((n & 0xF0L) >> 4) - 1)
# define RIGHT_WALL(n)(((n & 0xF00L) >> 8) - 1)
# define LEFT_WALL(n)(((n & 0xF000L) >> 12) - 1)
# define FLOOR(n)(((n & 0xF00000L) >> 20))
# define CEIL(n)(((n & 0xF0000L) >> 16))
# define SPRITE(n)((n & 0xF000000L) >> 24)
# define IS_SPRITE(n)((n & 0xF0000000L) >> 28)
# define EREASE_SPRITE(n)(n &= 0xFFFFFFFF00FFFFFFL)

# define MAPS_FOLDER "resources/maps/"
# define HUD_FOLDER "resources/images/hud/"
# define W_TEX_FOLDER "resources/images/wolf/"
# define M_TEX_FOLDER "resources/images/minecraft/"
# define MUSIC_FOLDER "resources/sounds/"
# define FONTS_FOLDER "resources/fonts/"

typedef unsigned int	t_uint;

typedef	struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef	struct	s_ivec
{
	int			x;
	int			y;
}				t_ivec;

typedef	struct	s_karta
{
	int			rows;
	int			cols;
	t_uint		**data;
}				t_karta;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*screen;
}				t_sdl;

#endif