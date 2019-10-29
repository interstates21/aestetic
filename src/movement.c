/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:21:26 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:51:14 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	smooth_movement(t_env *d, short *count, t_vec2f *mvt)
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
	to_iner(d, *mvt);
}

void		to_move_func(t_env *d)
{
	t_vec2f	mvt;
	short	count;
	int		protection;

	if (d->player.can_be_stomped)
		d->player.can_be_stomped--;
	if (!d->player.moving)
	{
		count = 0;
		ft_bzero(&mvt, sizeof(t_vec2f));
		smooth_movement(d, &count, &mvt);
		d->cam.pos.z += d->inertia.y;
		d->cam.pos.x += d->inertia.x;
	}
	else
		d->player.moving--;
	protection = 0;
	while (collision_player(d, &d->sectors[d->this_sect]))
		if (++protection > 6)
			break ;
	play_by_monst_colided(d, d->this_sect);
}
