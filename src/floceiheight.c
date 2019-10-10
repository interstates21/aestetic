#include "../includes/doom_nukem.h"

static void	get_sector_center(t_vec2f *v, t_wall *walls, int nWalls, int currentWall)
{
	int			i;
	t_vec2f		p;
	double		interp;

	p = walls[currentWall + i].point;
	interp = 1.0 / nWalls;
	v->x = 0;
	v->y = 0;
	i = -1;
	while (++i < nWalls)
		*v = v2_plus(*v, p);
	*v = v2_scale(*v, interp);
}
static double tanCalculations(double h, double slope, t_vec2f p, t_vec2f c) {
	return(h + tan(slope * M_PI / 180) * (p.x - c.x));
}

static double getAngle(double o, bool isAnimated) {
	double temp;

	temp = o * M_PI / 180;
	if (isAnimated)
		temp += ANIMATION_TIME;
	return temp;
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

	// return (h + tan(slope * M_PI / 180) * (p.x - center.x));
	return (tanCalculations(sect->ceilheight, sect->slopeceil, p, center));
	}
	print_err("0 sectors");
	return (1);
}

double	getFloorHeight(t_sector *sect, t_wall *walls, int16_t sectnum, t_vec2f p)
{
	t_vec2f		center;
	double		h;
	double		angle;

	if (sectnum >= 0) {
			h = sect->floorheight + (sect->is_elevator ? sin(ANIMATION_TIME) * 0.5 : 0);
			if (!(sect->slope))
				return (h);
	ft_putendl("1-end");
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
