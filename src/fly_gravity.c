#include "../includes/doom_nukem.h"

static void	decrease_fuel(t_data *d)
{
	d->player.is_flying -= 1;
	if (!d->player.is_flying)
	{
		if (d->slot1 && d->slot1->is_jetpack)
			d->slot1 = NULL;
		if (d->slot2 && d->slot2->is_jetpack)
			d->slot2 = NULL;
		if (d->slot3 && d->slot3->is_jetpack)
			d->slot3 = NULL;
	}
}

static void	fly_gravity_3(t_data *d)
{
	if (!(d->cam.pos.y > d->floorheightplayer + d->player.minimum_height))
		d->player.gravity = 0.0;
	if (!d->player.is_flying)
		d->player.gravity = 0.0;
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer
			- MINIMUM_CEIL_DIST)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->ceilheightplayer - MINIMUM_CEIL_DIST;
	}
}

static void	fly_gravity_2(t_data *d)
{
	if (d->keys[SDL_SCANCODE_SPACE])
	{
		if (d->cam.pos.y <= d->floorheightplayer + JUMP_FIX +
				d->player.minimum_height)
			d->player.gravity = JUMP_FORCE / 2;
		else
			d->player.gravity += FLYING_SPEED * (d->player.gravity < 0 ? 0.6
					: 0.3);
		d->cam.pos.y += FLYING_SPEED;
		decrease_fuel(d);
	}
	else if (d->keys[SDL_SCANCODE_LCTRL])
	{
		d->player.gravity -= (FLYING_SPEED * 0.5);
		d->cam.pos.y -= FLYING_SPEED;
	}
	fly_gravity_3(d);
}

void		fly_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
	{
		if (d->player.gravity < -0.20)
			player_fell(d);
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	if (!d->keys[SDL_SCANCODE_SPACE] && d->cam.pos.y <= d->floorheightplayer +
			JUMP_FIX + d->player.minimum_height)
	{
		normal_gravity(d);
		return ;
	}
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height &&
			!d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity -= 0.002;
	fly_gravity_2(d);
}
