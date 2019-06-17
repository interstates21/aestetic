#ifndef DOOM_H
# define DOOM_H

# include <time.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_render.h>
# include "libft.h"
#ifdef __APPLE__
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
#elif __linux__
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>

#endif

# define MAP_WIDTH 5
# define MAP_HEIGHT 6
# define WIDTH 1200
# define HEIGHT 600

typedef struct s_rgb {
	int r;
	int g;
	int b;
	int a;
}				t_rgb;

typedef enum { false, true } bool;
typedef struct s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface_sreen;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Event	event;
	Uint32		*pixels;
}				t_sdl;


# include "functions.h"

#endif
