/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:59:00 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/21 23:04:49 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	can_traverse(t_data *d, int i, t_wall *wall)
{
	double y_value;

	y_value = d->cam.pos.y + d->player.minimum_height;
	if (wall->neighborsect != -1 &&
		wall->is_transparent == false &&
		d->doorstate[i] > 0.7 &&
		y_value > get_floorheight_player(d, wall->neighborsect) +
			MINIMUM_HEIGHT_TO_WALK &&
		(d->sectors[wall->neighborsect].outdoor ||
			(d->cam.pos.y < get_ceilheight_player(d, wall->neighborsect) &&
			get_ceilheight_player(d, wall->neighborsect) -
				get_floorheight_player(d,
			wall->neighborsect) - MINIMUM_CEIL_DIST >
				d->player.minimum_height)))
		return (true);
	return (false);
}

t_vec2f	get_closest(t_vec2f a, t_vec2f b, t_vec2f p)
{
	t_vec2f a_to_p;
	t_vec2f	a_to_b;
	double	atb2;
	double	atp_dot_atb;
	double	plane;

	a_to_p = (t_vec2f){p.x - a.x, p.y - a.y};
	a_to_b = (t_vec2f){b.x - a.x, b.y - a.y};
	plane = (a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y) /
			(a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y);
	plane = CLAMP(plane, 0, 1);
	return ((t_vec2f){a.x + plane * a_to_b.x, a.y + plane * a_to_b.y});
}

bool	collided_v(t_vec2f *v, int *nw, t_data *d)
{
	if (v2_len(v[1]) < COLLISION_DIST)
	{
		if (can_traverse(d, nw[0], &d->walls[nw[0]]))
			return (collision(d, &d->sectors[d->walls[nw[0]].neighborsect]));
		else
		{
			d->cam.pos.x = v[0].x + v[1].x * COLLISION_DIST * 1.001 /
																v2_len(v[1]);
			d->cam.pos.z = v[0].y + v[1].y * COLLISION_DIST * 1.002 /
																v2_len(v[1]);
			return (true);
		}
	}
	return (false);
}

bool	collision(t_data *d, t_sector *sect)
{
	static int	recursion;
	t_vec2f		vect[2];
	double		dist;
	bool		collided;
	int			num_wall[2];

	collided = false;
	if (++recursion > 3)
	{
		--recursion;
		return (false);
	}
	num_wall[0] = sect->firstwallnum + sect->numwalls - 1;
	num_wall[1] = sect->firstwallnum;
	while (num_wall[1] < sect->firstwallnum + sect->numwalls)
	{
		vect[0] = get_closest(d->walls[num_wall[0]].point,
			d->walls[num_wall[1]].point, v3_to_v2(d->cam.pos));
		vect[1] = v2_min(v3_to_v2(d->cam.pos), vect[0]);
		collided_v(vect, num_wall, d);
		num_wall[0] = num_wall[1]++;
	}
	--recursion;
	return (collided);
}

bool	can_traverse_monster(t_data *d, int i, t_vec2f *pos, t_sector *sect)
{
	t_wall	*wall;
	int16_t	num_sec;

	wall = &d->walls[i];
	num_sec = sect - &d->sectors[0];
	if (wall->neighborsect != -1 && !(wall->is_transparent) &&
		d->doorstate[i] > 0.7 &&
		(get_floor_height(&d->sectors[num_sec], d->walls, num_sec, *pos) +
			MIN_HEIGHT_MONSTER_TO_WALK != get_floor_height(&d->sectors[num_sec],
				d->walls, num_sec, *pos))
		&& (d->sectors[wall->neighborsect].outdoor ||
		get_ceil_height(&d->sectors[num_sec], d->walls, num_sec, *pos) -
			get_floor_height(&d->sectors[num_sec], d->walls, num_sec, *pos) >
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

bool	collision_monster_wall(t_data *d, t_sector *sect, t_vec2f *pos,
															double dist_coll)
{
	static int	recursion;
	t_vec2f		vect[2];
	bool		collided;
	int			w[2];

	if (!(collided = false) && ++recursion > 3)
		return (false + (--recursion ? 0 : 0));
	w[0] = sect->firstwallnum + sect->numwalls - 1;
	w[1] = sect->firstwallnum;
	while (w[1] < sect->firstwallnum + sect->numwalls)
	{
		vect[0] = get_closest(d->walls[w[0]].point, d->walls[w[1]].point, *pos);
		vect[1] = v2_min(*pos, vect[0]);
		if (v2_len(vect[1]) < dist_coll)
		{
			if (can_traverse_monster(d, w[0], pos, sect))
				collided = collision_monster_wall(d,
					&d->sectors[d->walls[w[0]].neighborsect], pos, dist_coll);
			else
				collided = collided_value_one(pos, vect, dist_coll);
		}
		w[0] = w[1]++;
	}
	--recursion;
	return (collided);
}
