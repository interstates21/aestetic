#include "../includes/doom_nukem.h"

bool	can_traverse(t_data *d, int numb_wall, t_wall *wall)
{
	double y_value;

	y_value = d->cam.pos.y + d->player.minimum_height;
	if (wall->neighborsect != -1 &&
		wall->is_transparent == false &&
		d->doorstate[numb_wall] > 0.7 &&
		y_value > get_floorheight_player(d,
			wall->neighborsect) + MINIMUM_HEIGHT_TO_WALK &&
		(d->sectors[wall->neighborsect].outdoor ||
			(d->cam.pos.y < get_ceilheight_player(d, wall->neighborsect) &&
			get_ceilheight_player(d, wall->neighborsect) -
			get_floorheight_player(d, wall->neighborsect) -
							MINIMUM_CEIL_DIST > d->player.minimum_height)))
		return (true);
	return (false);
}

t_vec2f	get_closest(t_vec2f a, t_vec2f b, t_vec2f p)
{
	t_vec2f a_to_p;
	t_vec2f	a_to_b;
	double	t;

	a_to_p = (t_vec2f){p.x - a.x, p.y - a.y};
	a_to_b = (t_vec2f){b.x - a.x, b.y - a.y};
	t = (a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y)
		/ (a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y);
	t = CLAMP(t, 0, 1);
	return ((t_vec2f){a.x + t * a_to_b.x, a.y + t * a_to_b.y});
}

bool	collided_value(t_vec2f *v, int *nw, t_data *d)
{
	if (v2_len(v[1]) < COLLISION_DIST)
	{
		if (can_traverse(d, nw[0], &d->walls[nw[0]]))
			return (collision(d, &d->sectors[d->walls[nw[0]].neighborsect]));
		else
		{
			d->cam.pos.x = v[0].x + v[1].x * COLLISION_DIST / v2_len(v[1]);
			d->cam.pos.z = v[0].y + v[1].y * COLLISION_DIST / v2_len(v[1]);
			return (true);
		}
	}
	return (false);
}

bool	collision(t_data *d, t_sector *sect)
{
	static int	recursion;
	t_vec2f		vectors[2];
	bool		collided;
	int			num_of_wall[2];

	collided = false;
	if (++recursion > 3)
	{
		--recursion;
		return (false);
	}
	num_of_wall[0] = sect->firstwallnum + sect->numwalls - 1;
	num_of_wall[1] = sect->firstwallnum;
	while (num_of_wall[1] < sect->firstwallnum + sect->numwalls)
	{
		vectors[0] = get_closest(d->walls[num_of_wall[0]].point,
					d->walls[num_of_wall[1]].point, v3_to_v2(d->cam.pos));
		vectors[1] = v2_min(v3_to_v2(d->cam.pos), vectors[0]);
		collided = collided_value(vectors, num_of_wall, d);
		num_of_wall[0] = num_of_wall[1]++;
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
		d->doorstate[i] > 0.7 && (d->sectors[wall->neighborsect].outdoor ||
			getCeilHeight(&d->sectors[num_sec], d->walls, num_sec, *pos) -
			getFloorHeight(&d->sectors[num_sec], d->walls, num_sec, *pos) >
											SMALLEST_HEIGHT_FOR_MONSTERS))
		return (true);
	return (false);
}

bool	collided_monster_value(t_vec2f *v, double *nw, t_data *d,
		t_sector *sect)
{
	if (v2_len(v[1]) < nw[2])
	{
		if (can_traverse_monster(d, nw[0], &v[2], sect))
			return (collision_monster_wall(d,
				&d->sectors[d->walls[(int)nw[0]].neighborsect], &v[2], nw[2]));
		else
		{
			(&v[2])->x = v[0].x + v[1].x * nw[2] / v2_len(v[1]);
			(&v[2])->y = v[0].y + v[1].y * nw[2] / v2_len(v[1]);
			return (true);
		}
	}
	return (false);
}

bool	collision_monster_wall(t_data *d,
		t_sector *sect, t_vec2f *pos, double dist_coll)
{
	static int	recursion;
	t_vec2f		vectors[3];
	bool		collided;
	double		num_of_wall[3];

	collided = false;
	num_of_wall[2] = dist_coll;
	vectors[2] = *pos;
	if (++recursion > 3)
	{
		--recursion;
		return (false);
	}
	num_of_wall[0] = sect->firstwallnum + sect->numwalls - 1;
	num_of_wall[1] = sect->firstwallnum;
	while (num_of_wall[1] < sect->firstwallnum + sect->numwalls)
	{
		vectors[0] = get_closest(d->walls[(int)num_of_wall[0]].point,
									d->walls[(int)num_of_wall[1]].point, *pos);
		vectors[1] = v2_min(*pos, vectors[0]);
		collided = collided_monster_value(vectors, num_of_wall, d, sect);
		num_of_wall[0] = num_of_wall[1]++;
	}
	--recursion;
	return (collided);
}
