/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_monster.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:59:00 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:10:38 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	can_traverse_monster(t_env *d, int i, t_vec2f *pos, t_sec *sect)
{
	t_wall	*wall;
	int16_t	num_sec;

	wall = &d->walls[i];
	num_sec = sect - &d->sectors[0];
	if (wall->neighborsect != -1 && !(wall->is_transparent) &&
		d->door_active[i] > 0.7 &&
		(height_fl_val(&d->sectors[num_sec], d->walls, num_sec, *pos) +
			MIN_HEIGHT_MONSTER_TO_WALK != height_fl_val(&d->sectors[num_sec],
				d->walls, num_sec, *pos))
		&& (d->sectors[wall->neighborsect].outdoor ||
		height_cl_val(&d->sectors[num_sec], d->walls, num_sec, *pos) -
			height_fl_val(&d->sectors[num_sec], d->walls, num_sec, *pos) >
				SMALLEST_HEIGHT_FOR_MONSTERS))
		return (true);
	return (false);
}

bool	collided_value_one(t_vec2f *pos, t_vec2f *v, double dist_coll)
{
	pos->x = v[0].x + v[1].x * dist_coll * 1.001 / v2_len(v[1]);
	pos->y = v[0].y + v[1].y * dist_coll * 1.002 / v2_len(v[1]);
	return (true);
}

bool	collision_monster(t_env *d, t_sec *sect, t_vec2f *pos,
															double dist_coll)
{
	static int	recursion;
	t_vec2f		v[2];
	bool		collided;
	int			w[2];

	if (!(collided = false) && ++recursion > 3)
		return (false + (--recursion ? 0 : 0));
	w[0] = sect->firstwallnum + sect->n_walls - 1;
	w[1] = sect->firstwallnum;
	while (w[1] < sect->firstwallnum + sect->n_walls)
	{
		v[0] = to_close_val(d->walls[w[0]].point, d->walls[w[1]].point, *pos);
		v[1] = v2_min(*pos, v[0]);
		if (v2_len(v[1]) < dist_coll)
		{
			if (can_traverse_monster(d, w[0], pos, sect))
				collided = collision_monster(d,
					&d->sectors[d->walls[w[0]].neighborsect], pos, dist_coll);
			else
				collided = collided_value_one(pos, v, dist_coll);
		}
		w[0] = w[1]++;
	}
	--recursion;
	return (collided);
}
