#include "../includes/doom_nukem.h"

double	get_floorheight_player(t_data *d, int16_t sectnum)
{
	double floorHeight;
	t_vec2f	v;
	t_sector *s = &d->sectors[sectnum];

	v.x = d->cam.pos.x;
	v.y = d->cam.pos.z;
	floorHeight = getFloorHeight(s, d->walls, sectnum, v);
	return (floorHeight);
}

double	get_floordh(t_data *d, t_sector *sect, t_vec2f v)
{
	double floorHeight;
	int16_t n;
	t_sector *s;
	double res;

    if (!sect)
        print_err("get ceil sector is null");
	n = sect - d->sectors;
	s = &d->sectors[n];
	floorHeight = getFloorHeight(s, d->walls, n, v);
	res = floorHeight - d->cam.pos.y;
	return (res);
}

double	getFloorHeight(t_sector *sect, t_wall *walls, int16_t sectnum, t_vec2f p)
{
	t_vec2f		center;
	double		h;
	double		angle;

	if (sectnum >= 0) {
			h = calculateMaxFloorH(sect);
			if (!(sect->slope))
				return (h);
	get_sector_center(&center, walls, sect->numwalls, sect->firstwallnum);
	angle = getAngle(sect->slope_orientation, sect->is_animatedslope);
	p = v2_min(p, center);
	v2_rot(&p, angle);
	p = v2_plus(p, center);
	return (tanCalculations(h, sect->slope, p, center));
	}
	print_err("0 sectors");
	return (1);
}

