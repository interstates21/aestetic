#include "alt.h"

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
