#include "../includes/doom_nukem.h"

double	get_ceilheight_player(t_data *d, int16_t sectnum)
{
	double ceilHeight;
	t_vec2f	v;
	t_sector *s;

	v.x = d->cam.pos.x;
	v.y = d->cam.pos.z;
	s = &d->sectors[sectnum];
	ceilHeight = getCeilHeight(s, d->walls, sectnum, v);		
	return (ceilHeight);
}

double	get_ceildh(t_data *d, t_sector *sect, t_vec2f v)
{
	double ceilHeight;
	int16_t n;
	t_sector *s;
	double	res;

    if (!sect)
        print_err("get ceil sector is null");
	n = sect - d->sectors;
	s = &d->sectors[n];

	ceilHeight = getCeilHeight(s, d->walls, n, v);
	res = ceilHeight - d->cam.pos.y;
	return (res);
}

double	getCeilHeight(t_sector *sect, t_wall *walls, int16_t sectnum, t_vec2f p)
{
	t_vec2f		center;
	double		angle;

	if (sectnum >= 0) {
		if (!(sect->slopeceil))
			return (sect->ceilheight);
	    get_sector_center(&center, walls, sect->numwalls, sect->firstwallnum);
	    angle = getAngle(sect->slopeceil_orientation, sect->is_animatedslopeceil);
	    p = v2_min(p, center);
	    v2_rot(&p, angle);
	    p = v2_plus(p, center);
	    return (tanCalculations(sect->ceilheight, sect->slopeceil, p, center));
	}
	print_err("0 sectors");
	return (1);
}