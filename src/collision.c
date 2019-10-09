#include "../includes/doom_nukem.h"


bool	can_traverse(t_data *d, int i, t_wall *wall)
{
	int16_t neighbor;

	neighbor = wall->neighborsect;
	return (wall->neighborsect != -1 &&
			wall->is_transparent == false &&
			d->doorstate[i] > 0.7 &&
			d->cam.pos.y + d->player.minimum_height > get_floorheight_player(d,
			neighbor) + MINIMUM_HEIGHT_TO_WALK &&
			(d->sectors[neighbor].outdoor ||
			(d->cam.pos.y < get_ceilheight_player(d, neighbor) &&
			get_ceilheight_player(d, neighbor) - get_floorheight_player(d,
			neighbor) - MINIMUM_CEIL_DIST > d->player.minimum_height)));
}

t_vec2f	get_closest(t_vec2f a, t_vec2f b, t_vec2f p)
{
	t_vec2f a_to_p;
	t_vec2f	a_to_b;
	double	atb2;
	double	atp_dot_atb;
	double	t;

	a_to_p = (t_vec2f){p.x - a.x, p.y - a.y};
	a_to_b = (t_vec2f){b.x - a.x, b.y - a.y};
	atb2 = a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y;
	atp_dot_atb = a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y;
	t = atp_dot_atb / atb2;
	t = CLAMP(t, 0, 1);
	return ((t_vec2f){a.x + t * a_to_b.x, a.y + t * a_to_b.y});
}

bool	collision(t_data *d, t_sector *sect)
{
	static int	recursion;
	t_vec2f		v[2];
	double		dist;
	bool		collided;
	int			i[2];

	if (!(collided = false) && ++recursion > 3)
		return (false + (--recursion ? 0 : 0));
	i[0] = sect->firstwallnum + sect->numwalls - 1;
	i[1] = sect->firstwallnum;
	while (i[1] < sect->firstwallnum + sect->numwalls)
	{
		v[0] = get_closest(d->walls[i[0]].point, d->walls[i[1]].point,
				v3_to_v2(d->cam.pos));
		v[1] = v2_min(v3_to_v2(d->cam.pos), v[0]);
		if ((dist = v2_len(v[1])) < COLLISION_DIST)
			(can_traverse(d, i[0], &d->walls[i[0]])) ? (collided |=
			collision(d, &d->sectors[d->walls[i[0]].neighborsect])) :
			((d->cam.pos.x = v[0].x + v[1].x * COLLISION_DIST * 1.001 /
			dist) && (d->cam.pos.z = v[0].y + v[1].y * COLLISION_DIST *
			1.002 / dist) && (collided = true));
		i[0] = i[1]++;
	}
	return (collided + (--recursion ? 0 : 0));
}


bool	can_traverse_monster(t_data *d, int i, t_vec2f *pos, t_sector *sect)
{
	double	floorHeight;
	double	roofHeight;
	t_wall	*wall;
	int16_t	sectNum;

	wall = &d->walls[i];
	sectNum = sect - &d->sectors[0];
	floorHeight = getFloorHeight(&d->sectors[sectNum], d->walls, sectNum, *pos);
	roofHeight = getCeilHeight(&d->sectors[sectNum], d->walls, sectNum, *pos);
	return (wall->neighborsect != -1 && !(wall->is_transparent) && d->doorstate[i] > 0.7 &&
			(floorHeight + MIN_HEIGHT_MONSTER_TO_WALK != floorHeight)
			&& (d->sectors[wall->neighborsect].outdoor ||
			roofHeight - floorHeight > SMALLEST_HEIGHT_FOR_MONSTERS));
}


bool	collision_monster_wall(t_data *d,
		t_sector *sect, t_vec2f *pos, double dist_coll)
{
	static int	recursion;
	t_vec2f		v[2];
	double		dist;
	bool		collided;
	int			i[2];

	if (!(collided = false) && ++recursion > 3)
		return (false + (--recursion ? 0 : 0));
	i[0] = sect->firstwallnum + sect->numwalls - 1;
	i[1] = sect->firstwallnum;
	while (i[1] < sect->firstwallnum + sect->numwalls)
	{
		v[0] = get_closest(d->walls[i[0]].point, d->walls[i[1]].point,
				*pos);
		v[1] = v2_min(*pos, v[0]);
		if ((dist = v2_len(v[1])) < dist_coll)
			(can_traverse_monster(d, i[0], pos, sect)) ?
				(collided |= collision_monster_wall(d,
				&d->sectors[d->walls[i[0]].neighborsect], pos, dist_coll)) :
				((pos->x = v[0].x + v[1].x * dist_coll * 1.001 /
				dist) && (pos->y = v[0].y + v[1].y * dist_coll *
				1.002 / dist) && (collided = true));
		i[0] = i[1]++;
	}
	return (collided + (--recursion ? 0 : 0));
}
