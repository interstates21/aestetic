/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jumping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 04:52:13 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 19:55:23 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	four_action(t_data *d)
{
	if (d->keys[SDL_SCANCODE_LCTRL] && d->player.minimum_height >
				MINIMUM_CROUCH_HEIGHT + CROUCH_SPEED)
		d->player.minimum_height -= CROUCH_SPEED;
	if (!d->keys[SDL_SCANCODE_LCTRL] && d->player.minimum_height
				< MINIMUM_HEIGHT)
		if ((d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST)
					> d->player.minimum_height + CROUCH_SPEED)
			d->player.minimum_height += CROUCH_SPEED;
}

void	jump_action(t_data *d, int mode)
{
	if (mode < 2)
	{
		mode == 0 ? player_fell(d) : true;
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	else if (mode < 4)
	{
		d->player.gravity -= 0.004;
		mode == 2 ? (d->player.gravity += 0.0015) : true;
	}
	else if (mode == 4)
		four_action(d);
	else if (mode == 5)
		(d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST <=
			MINIMUM_HEIGHT) ? (d->player.minimum_height = d->ceilheightplayer -
				d->floorheightplayer - MINIMUM_CEIL_DIST - CROUCH_SPEED) :
				(d->player.minimum_height = MINIMUM_HEIGHT);
	else if (mode == 6)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->ceilheightplayer - MINIMUM_CEIL_DIST;
	}
}

void	normal_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
		d->player.gravity < -0.16 ? jump_action(d, 0) : jump_action(d, 1);
	if (d->cam.pos.y <= d->floorheightplayer + JUMP_FIX +
			d->player.minimum_height && d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity = JUMP_FORCE;
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height)
		(d->player.gravity > 0 && d->keys[SDL_SCANCODE_SPACE]) ?
										jump_action(d, 2) : jump_action(d, 3);
	if (d->cam.pos.y <= d->floorheightplayer + d->player.minimum_height)
		jump_action(d, 4);
	if (d->keys[SDL_SCANCODE_SPACE])
		jump_action(d, 5);
	if (d->player.minimum_height < MINIMUM_CROUCH_HEIGHT)
		d->player.minimum_height += CROUCH_SPEED + CROUCH_SPEED + CROUCH_SPEED;
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer
			- MINIMUM_CEIL_DIST)
		jump_action(d, 6);
}

void	jump(t_data *d)
{
	if (d->player.is_flying)
		fly_mode(d);
	else
		normal_gravity(d);
}
