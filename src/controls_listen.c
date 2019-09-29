
#include "alt.h"

void	listen_controls(t_player *player, bool *end, t_controller *controller)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{

							SDL_SetRelativeMouseMode(SDL_TRUE);

		if (event.type == SDL_QUIT)
			*end = true;
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

				if (event.key.keysym.sym == SDLK_ESCAPE)
				*end = true;

				if (event.key.keysym.sym == SDLK_w)
					controller->move_forw = event.type == SDL_KEYDOWN;
				if (event.key.keysym.sym == SDLK_s)
					controller->move_back = event.type == SDL_KEYDOWN;
				if (event.key.keysym.sym == SDLK_a)
					controller->rot_left = event.type == SDL_KEYDOWN;
				if (event.key.keysym.sym == SDLK_d)
					controller->rot_right = event.type == SDL_KEYDOWN;
				if (event.key.keysym.sym == SDLK_SPACE)
					if (controller->ground)
					{
						player->dir.z += 0.5;
						controller->falling = 1;
					}
				if (event.key.keysym.sym == SDLK_LCTRL)
				{
					controller->ducking = event.type == SDL_KEYDOWN;
					controller->falling = 1;
				}
		

		}

	}
}
