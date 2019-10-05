#include "../includes/doom_nukem.h"

static void	check_crouch(t_data *d)
{
	if (d->cam.pos.y <= d->floorheightplayer + d->player.minimum_height)
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
	if (d->keys[SDL_SCANCODE_SPACE])
	{
		if (d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST <=
			MINIMUM_HEIGHT)
			d->player.minimum_height = d->ceilheightplayer -
									   d->floorheightplayer - MINIMUM_CEIL_DIST - CROUCH_SPEED;
		else
			d->player.minimum_height = MINIMUM_HEIGHT;
	}
	if (d->player.minimum_height < MINIMUM_CROUCH_HEIGHT)
		d->player.minimum_height += CROUCH_SPEED + CROUCH_SPEED + CROUCH_SPEED;
}

static void	smooth_movement(t_data *d, short *count, t_vec2f *mvt)
{
	if (d->keys[SDL_SCANCODE_W] && ++*count)
	{
		mvt->y += d->cam.cos * MOVE_SPEED;
		mvt->x += d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_S] && ++*count)
	{
		mvt->y -= d->cam.cos * MOVE_SPEED;
		mvt->x -= d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_A] && ++*count)
	{
		mvt->y += d->cam.sin * MOVE_SPEED;
		mvt->x -= d->cam.cos * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_D] && ++*count)
	{
		mvt->y -= d->cam.sin * MOVE_SPEED;
		mvt->x += d->cam.cos * MOVE_SPEED;
	}
	if (*count == 2)
		*mvt = v2_scale(*mvt, 0.707);
	inertia(d, *mvt);
}

void	normal_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
	{
		if (d->player.gravity < -0.16)
			player_fell(d);
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	if (d->cam.pos.y <= d->floorheightplayer + JUMP_FIX +
						d->player.minimum_height && d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity = JUMP_FORCE;
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height)
	{
		d->player.gravity -= 0.004;
		if (d->player.gravity > 0 && d->keys[SDL_SCANCODE_SPACE])
			d->player.gravity += 0.0015;
	}
	check_crouch(d);
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer
															 - MINIMUM_CEIL_DIST)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->ceilheightplayer - MINIMUM_CEIL_DIST;
	}
}

void	jump(t_data *d)
{
	if (d->player.is_flying)
		fly_gravity(d);
	else
		normal_gravity(d);
}

void	movement(t_data *d)
{
	t_vec2f	mvt;
	short	count;
	int		protection;

	if (d->player.can_be_stomped)
		d->player.can_be_stomped--;
	if (!d->player.can_move)
	{
		count = 0;
		ft_bzero(&mvt, sizeof(t_vec2f));
		smooth_movement(d, &count, &mvt);
		d->cam.pos.z += d->inertia.y;
		d->cam.pos.x += d->inertia.x;
	}
	else
		d->player.can_move--;
	protection = 0;
	while (collision(d, &d->sectors[d->cursectnum]))
		if (++protection > 6)
			break ;
	collision_with_monster(d, d->cursectnum);
}
