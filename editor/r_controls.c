#include "../includes/editor.h"

void	listen_controls(bool *end)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		// SDL_SetRelativeMouseMode(SDL_TRUE);
		if (event.type == SDL_QUIT)
			*end = true;
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
				    *end = true;
				if (event.key.keysym.sym == SDLK_w)
                    ft_putstr("hello");

		}
		   
	}

}
