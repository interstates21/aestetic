/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:11:09 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:17:13 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	can_traverse(t_env *d, int i, t_wall *wall)
{
	double y_value;

	y_value = d->cam.pos.y + d->player.min_h;
	if (wall->neighborsect != -1 &&
		wall->is_transparent == false &&
		d->door_active[i] > 0.7 &&
		y_value > height_play_fl_val(d, wall->neighborsect) +
			MINIMUM_HEIGHT_TO_WALK &&
		(d->sectors[wall->neighborsect].outdoor ||
			(d->cam.pos.y < height_play_cl_val(d, wall->neighborsect) &&
			height_play_cl_val(d, wall->neighborsect) -
				height_play_fl_val(d,
			wall->neighborsect) - MINIMUM_CEIL_DIST >
				d->player.min_h)))
		return (true);
	return (false);
}

t_vec2f	to_close_val(t_vec2f a, t_vec2f b, t_vec2f p)
{
	t_vec2f a_to_p;
	t_vec2f	a_to_b;
	double	atb2;
	double	atp_dot_atb;
	double	plane;

	a_to_p = new_v2(p.x - a.x, p.y - a.y);
	a_to_b = new_v2(b.x - a.x, b.y - a.y);
	plane = (a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y) /
			(a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y);
	plane = CLAMP(plane, 0, 1);
	return (new_v2(a.x + plane * a_to_b.x, a.y + plane * a_to_b.y));
}

bool	collided_v(t_vec2f *v, int *nw, t_env *d)
{
	if (v2_len(v[1]) < COLLISION_DIST)
	{
		if (can_traverse(d, nw[0], &d->walls[nw[0]]))
			return (collision_player(d,
				&d->sectors[d->walls[nw[0]].neighborsect]));
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

bool	collision_player(t_env *d, t_sec *sect)
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
	num_wall[0] = sect->firstwallnum + sect->n_walls - 1;
	num_wall[1] = sect->firstwallnum;
	while (num_wall[1] < sect->firstwallnum + sect->n_walls)
	{
		vect[0] = to_close_val(d->walls[num_wall[0]].point,
			d->walls[num_wall[1]].point, v3_to_v2(d->cam.pos));
		vect[1] = v2_min(v3_to_v2(d->cam.pos), vect[0]);
		collided_v(vect, num_wall, d);
		num_wall[0] = num_wall[1]++;
	}
	--recursion;
	return (collided);
}
