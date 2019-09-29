
#include "alt.h"

void	keyboard_input(t_player *player, bool *end, t_controller *controller)
{
	SDL_Event ev;

	controller->checkmouse_way = true;
	while (SDL_PollEvent(&ev))
	{

		if (ev.type == SDL_QUIT)
			*end = true;
		if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
		{
			if (ev.type == SDL_KEYDOWN)
				if (ev.key.keysym.sym == SDLK_RCTRL)
				{
					SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() ?
														SDL_FALSE : SDL_TRUE);
					controller->move_forw = false;
					controller->move_back = false;
					controller->rot_left = false;
					controller->rot_right = false;
					controller->checkmouse_way = false;
				}
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				*end = true;
			if (SDL_GetRelativeMouseMode())
			{
																	printf("--%d --\n", controller->move_forw );
									ft_putendl("en");
				if (ev.key.keysym.sym == SDLK_w) {

					controller->move_forw = ev.type == SDL_KEYDOWN;
				}
				if (ev.key.keysym.sym == SDLK_s)
					controller->move_back = ev.type == SDL_KEYDOWN;
				if (ev.key.keysym.sym == SDLK_a)
					controller->rot_left = ev.type == SDL_KEYDOWN;
				if (ev.key.keysym.sym == SDLK_d)
					controller->rot_right = ev.type == SDL_KEYDOWN;
				if (ev.key.keysym.sym == SDLK_SPACE)
				{
					if (controller->ground)
					{
						player->dir.z += 0.5;
						controller->falling = 1;
					}
				}
				if (ev.key.keysym.sym == SDLK_LCTRL)
				{
					controller->ducking = ev.type == SDL_KEYDOWN;
					controller->falling = 1;
				}
			}
		}
	}
}

void	mouse_aiming(t_player *player, t_controller *controller)
{
	SDL_GetRelativeMouseState(&controller->mouse.x, &controller->mouse.y);
	if (SDL_GetRelativeMouseMode() && controller->checkmouse_way)
	{
		player->angle += controller->mouse.x * 0.007f;
		controller->yaw = clamp(controller->yaw - controller->mouse.y * (-0.025f), -5, 5);
		player->yaw = controller->yaw - player->dir.z * 0.5f;
	}
}