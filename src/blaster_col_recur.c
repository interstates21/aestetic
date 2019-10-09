#include "../includes/doom_nukem.h"

static void		set_var(t_data *d, uint16_t sect_to_scan, short *i,
		short *j)
{
	*i = d->sectors[sect_to_scan].firstwallnum;
	*j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls - 1;
}

static int16_t	set_var_2(t_data *d, uint16_t sect_to_scan, double *dist,
		bool hit_all)
{
	*dist = find_closest_wall_dist(d, sect_to_scan);
	return (scan_sect_point_line(d, sect_to_scan, *dist, hit_all));
}

static bool		check_dists(double dist, t_data *d, short i,
		short j)
{
	double	tmp_dist;

	if (dist == -1)
		return (true);
	tmp_dist = get_dist_to_intersect_wall(d, d->walls[j].point,
			d->walls[i].point);
	return (tmp_dist < dist);
}

static bool		check_condition_inside_wall(t_data *d, short i, short j)
{
	t_vec2f tmp;
	t_vec2f	tmp2;

	tmp2 = (t_vec2f){d->cam.pos.x + 1000 * d->cam.sin,
		d->cam.pos.z + 1000 * d->cam.cos};
	tmp = intersect(v3_to_v2(d->cam.pos), tmp2,
			d->walls[j].point, d->walls[i].point);
	return (is_inside_vec2f(d->walls[j].point, d->walls[i].point, tmp) &&
			is_inside_vec2f(v3_to_v2(d->cam.pos), tmp2, tmp));
}

int16_t			recur_scan_point_line(t_data *d,
		int16_t sect_to_scan, int16_t old_sect, bool hit_all)
{
	short		i;
	short		j;
	double		dist;
	int16_t		id;

	set_var(d, sect_to_scan, &i, &j);
	id = set_var_2(d, sect_to_scan, &dist, hit_all);
	if (!hit_all && id != -1)
		return (id);
	while (i < d->sectors[sect_to_scan].firstwallnum +
			d->sectors[sect_to_scan].numwalls)
	{
		if (d->walls[j].neighborsect != -1 && d->walls[j].neighborsect !=
				old_sect && d->doorstate[j] > 0.7)
			if (check_dists(dist, d, i, j) && check_condition_inside_wall(d, i,
						j))
			{
				return (recur_scan_point_line(d, d->walls[j].neighborsect,
							sect_to_scan, hit_all));
			}
		j = i++;
	}
	return (id);
}
