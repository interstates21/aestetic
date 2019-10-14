#include "../includes/doom_nukem.h"

double calculateMaxFloorH(t_sector *s) {
	double n;

	n = 0;
	if (s->is_elevator)
		n += sin(ANIMATION_TIME) * 0.5;
	n += s->floorheight;
    return (n);
}
void	get_sector_center(t_vec2f *v, t_wall *walls, int nWalls, int currentWall)
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

double tanCalculations(double h, double slope, t_vec2f p, t_vec2f c) {
	return(h + tan(slope * M_PI / 180) * (p.x - c.x));
}

double getAngle(double o, bool isAnimated) {
	double temp;

	temp = o * M_PI / 180;
	if (isAnimated)
		temp += ANIMATION_TIME;
	return temp;
}

double calculateFloorHeightEpsilon(double h) {
	return (h > 5 ? 1.2 : 1.1);
}