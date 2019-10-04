#include "../includes/doom_nukem.h"

#define TURN_SPEED 0.02

void	update_doors(t_data *d)
{
	int i;

	i = -1;
	while (++i < MAXNUMWALLS)
	{
		if (!d->walls[i].is_door || d->walls[i].neighborsect == -1)
			d->doorstate[i] = 1;
		else
		{
			d->doorstate[i] += d->dooranimstep[i];
			if (d->doorstate[i] >= 1 || d->doorstate[i] <= 0)
			{
				d->doorstate[i] = CLAMP(d->doorstate[i], 0, 1);
				d->dooranimstep[i] = 0;
			}
		}
	}
}

#define DEPTH_TO_SCAN 10

void	update(t_data *d)
{
	int16_t	sect;

	if (d->player.health <= 0)
		handle_respawn(d);
	if (d->sectors[d->cursectnum].is_finish)
		handle_finish(d);
	update_doors(d);
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	movement(d);
	asset_collision(d);
	if ((sect = update_cursect_smart(d, DEPTH_TO_SCAN, v3_to_v2(d->cam.pos),
					d->cursectnum)) != -1)
	{
		if (sect != d->cursectnum && d->cam.pos.y < get_floorheight_player(d,
					sect) + d->player.minimum_height)
			d->player.minimum_height = d->cam.pos.y - get_floorheight_player(d,
					sect);
		d->cursectnum = sect;
	}
	update_2(d);
}
