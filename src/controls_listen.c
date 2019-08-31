/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_listen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:05:56 by bdeomin           #+#    #+#             */
/*   Updated: 2019/08/28 20:19:32 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"

void	listen_controls(t_player *player, bool *end, t_controller *controller)
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
						player->motion.z += 0.5;
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
	SDL_GetRelativeMouseState(&controller->mouse_x, &controller->mouse_y);
	if (SDL_GetRelativeMouseMode() && controller->checkmouse_way)
	{
		player->angle += controller->mouse_x * 0.007f;
		controller->yaw = clamp(controller->yaw - controller->mouse_y * (-0.025f), -5, 5);
		player->yaw = controller->yaw - player->motion.z * 0.5f;
	}
}
