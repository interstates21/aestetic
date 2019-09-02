#include "../includes/alt.h"

double		x_prod(t_v2f a, t_v2f b)
{
	return (a.x * b.y - a.y * b.x);
}

void		rotate_z(t_v2f *p, float teta)
{
	float tmp;
	float cos_teta;
	float sin_teta;

	teta *= M_PI / 180.0;
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	tmp = p->x;
	p->x = p->x * cos_teta - p->y * sin_teta;
	p->y = tmp * sin_teta + p->y * cos_teta;
}
