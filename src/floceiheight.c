#include "../includes/doom_nukem.h"

t_vec2f	get_sector_center(t_data *d, t_sector *sect)
{
	int		i;
	t_vec2f	center;

	center = (t_vec2f){0, 0};
	i = -1;
	while (++i < sect->numwalls)
		center = v2_plus(center, d->walls[sect->firstwallnum + i].point);
	return (v2_scale(center, 1.0 / sect->numwalls));
}

t_vec2f	rotate_point(t_vec2f p, t_vec2f center, double angle)
{
	p = v2_min(p, center);
	p = (t_vec2f){p.x * cos(angle) - p.y * sin(angle),
			p.x * sin(angle) + p.y * cos(angle)};
	return (v2_plus(p, center));
}


double	get_floceiheight(t_data *d, int16_t sectnum, t_vec2f p, bool is_floor)
{
	t_sector	*sect;

	if (sectnum < 0)
		exit(printf("bad sectnum\n"));
	sect = &d->sectors[sectnum];
	return (is_floor ? sect->floorheight : sect->ceilheight) + ((is_floor &&
	sect->is_elevator) ? sin(SDL_GetTicks() / 2000.0) : 0);
}

/*
double	get_floceiheight(t_data *d, int16_t sectnum, t_vec2f p, bool is_floor)
{
	t_sector	*sect;
	t_vec2f		center;
	double		h;
	double		slope;

	if (sectnum < 0)
		exit(printf("bad sectnum\n"));
	sect = &d->sectors[sectnum];
	h = (is_floor ? sect->floorheight : sect->ceilheight) + ((is_floor &&
				sect->is_elevator) ? sin(SDL_GetTicks() / 1000.0) * 0.5 : 0);
	slope = is_floor ? sect->slope : sect->slopeceil;
	if (slope == 0)
		return (h);
	center = get_sector_center(d, sect);
	p = rotate_point(p, center, ((is_floor ? sect->slope_orientation :
			sect->slopeceil_orientation) * M_PI / 180) + (((is_floor &&
			sect->is_animatedslope) || (!is_floor &&
			sect->is_animatedslopeceil)) ? (SDL_GetTicks() / 1000.0) : 0));
	return (h + tan(slope * M_PI / 180) * (p.x - center.x));
}
*/
