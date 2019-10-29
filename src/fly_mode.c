/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:03:13 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:24:26 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static bool	decrease_fuel(t_env *d)
{
	d->player.flying -= 1;
	if (d->player.flying)
		return (true);
	if (d->vslutiak && d->slot2->is_jetpack)
		d->vslutiak = NULL;
	if (d->slot3 && d->slot3->is_jetpack)
		d->slot3 = NULL;
	return (true);
}

double		get_gravity(double gravitation)
{
	if (gravitation < 0)
		return (0.6);
	else
		return (0.3);
}

void		what_doing(t_env *d, int mode)
{
	double	pos_heigh;

	pos_heigh = d->player_floor_h + d->player.min_h;
	if (mode == 0)
	{
		d->player.gravity < -0.20 ? play_active(d) : true;
		d->player.gravity = 0.0;
		d->cam.pos.y = pos_heigh;
	}
	else if (mode == 1)
		(d->cam.pos.y <= d->player_floor_h + JUMP_FIX +
			d->player.min_h) ? ((d->player.gravity = JUMP_FORCE / 2) &&
			(d->cam.pos.y += FLYING_SPEED) && decrease_fuel(d)) : (
			(d->player.gravity += FLYING_SPEED * get_gravity(d->player.gravity))
			&& (d->cam.pos.y += FLYING_SPEED) && decrease_fuel(d));
	else if (mode == 2)
	{
		d->player.gravity -= (FLYING_SPEED * 0.5);
		d->cam.pos.y -= FLYING_SPEED;
	}
	else if (mode == 3)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = (d->player_ceil_h - MINIMUM_CEIL_DIST);
	}
}

void		fly_mode(t_env *d)
{
	double	pos_heigh;

	pos_heigh = d->player_floor_h + d->player.min_h;
	if (d->cam.pos.y < pos_heigh)
		what_doing(d, 0);
	if (!d->keys[SDL_SCANCODE_SPACE] && d->cam.pos.y <= d->player_floor_h +
			JUMP_FIX + d->player.min_h)
	{
		normal_mode(d);
		return ;
	}
	if (d->cam.pos.y > pos_heigh && !d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity -= 0.002;
	if (d->keys[SDL_SCANCODE_SPACE])
		what_doing(d, 1);
	else if (d->keys[SDL_SCANCODE_LCTRL])
		what_doing(d, 2);
	if (!(d->cam.pos.y > pos_heigh))
		d->player.gravity = 0.0;
	if (!d->player.flying)
		d->player.gravity = 0.0;
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->this_sect].outdoor && d->cam.pos.y > d->player_ceil_h
			- MINIMUM_CEIL_DIST)
		what_doing(d, 3);
}
