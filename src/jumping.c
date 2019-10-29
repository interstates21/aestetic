/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jumping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 04:52:13 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:50:11 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	four_action(t_env *d)
{
	if (d->keys[SDL_SCANCODE_LCTRL] && d->player.min_h >
				MINIMUM_CROUCH_HEIGHT + CROUCH_SPEED)
		d->player.min_h -= CROUCH_SPEED;
	if (!d->keys[SDL_SCANCODE_LCTRL] && d->player.min_h
				< MINIMUM_HEIGHT)
		if ((d->player_ceil_h - d->player_floor_h - MINIMUM_CEIL_DIST)
					> d->player.min_h + CROUCH_SPEED)
			d->player.min_h += CROUCH_SPEED;
}

void	jump_action(t_env *d, int mode)
{
	if (mode < 2)
	{
		mode == 0 ? play_active(d) : true;
		d->player.gravity = 0.0;
		d->cam.pos.y = d->player_floor_h + d->player.min_h;
	}
	else if (mode < 4)
	{
		d->player.gravity -= 0.004;
		mode == 2 ? (d->player.gravity += 0.0015) : true;
	}
	else if (mode == 4)
		four_action(d);
	else if (mode == 5)
		(d->player_ceil_h - d->player_floor_h - MINIMUM_CEIL_DIST <=
			MINIMUM_HEIGHT) ? (d->player.min_h = d->player_ceil_h -
				d->player_floor_h - MINIMUM_CEIL_DIST - CROUCH_SPEED) :
				(d->player.min_h = MINIMUM_HEIGHT);
	else if (mode == 6)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->player_ceil_h - MINIMUM_CEIL_DIST;
	}
}

void	normal_mode(t_env *d)
{
	if (d->cam.pos.y < d->player_floor_h + d->player.min_h)
		d->player.gravity < -0.16 ? jump_action(d, 0) : jump_action(d, 1);
	if (d->cam.pos.y <= d->player_floor_h + JUMP_FIX +
			d->player.min_h && d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity = JUMP_FORCE;
	if (d->cam.pos.y > d->player_floor_h + d->player.min_h)
		(d->player.gravity > 0 && d->keys[SDL_SCANCODE_SPACE]) ?
										jump_action(d, 2) : jump_action(d, 3);
	if (d->cam.pos.y <= d->player_floor_h + d->player.min_h)
		jump_action(d, 4);
	if (d->keys[SDL_SCANCODE_SPACE])
		jump_action(d, 5);
	if (d->player.min_h < MINIMUM_CROUCH_HEIGHT)
		d->player.min_h += CROUCH_SPEED + CROUCH_SPEED + CROUCH_SPEED;
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->this_sect].outdoor && d->cam.pos.y > d->player_ceil_h
			- MINIMUM_CEIL_DIST)
		jump_action(d, 6);
}

void	jumping(t_env *d)
{
	if (d->player.flying)
		fly_mode(d);
	else
		normal_mode(d);
}
