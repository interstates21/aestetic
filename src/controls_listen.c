/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_listen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:05:56 by bdeomin           #+#    #+#             */
/*   Updated: 2019/08/23 18:25:41 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"

void	keyboard_input(struct player *player, bool *end, t_controller *controller)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			*end = true;
		if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
		{
			if (ev.type == SDL_KEYDOWN)
				if (ev.key.keysym.sym == SDLK_RCTRL)
					SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() ?
														SDL_FALSE : SDL_TRUE);
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				*end = true;
			if (SDL_GetRelativeMouseMode())
			{
				if (ev.key.keysym.sym == SDLK_w)
					controller->move_forw = ev.type == SDL_KEYDOWN;
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
						player->velocity.z += 0.5;
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
