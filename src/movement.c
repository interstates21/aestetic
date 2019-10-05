#include "../includes/doom_nukem.h"

void	smooth_movement(t_data *d, short *count, t_vec2f *mvt)
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
