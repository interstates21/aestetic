#include "../includes/doom_nukem.h"

void	inertia(t_data *d, t_vec2f mvt)
{
	double	angle;

	d->inertia.x += mvt.x;
	d->inertia.y += mvt.y;
	if (v2_len(d->inertia) > MAX_INERTIA)
	{
		angle = atan2(d->inertia.y, d->inertia.x) - M_PI_2;
		d->inertia = (t_vec2f){ 0.0, MAX_INERTIA };
		actualize_dir(angle, &d->inertia);
	}
	if (v2_len(d->inertia) > 0.001)
		d->inertia = v2_scale(d->inertia, 0.9);
	else
	{
		d->inertia.x = 0;
		d->inertia.y = 0;
	}
}

void	change_inertia(t_data *d, double angle, double length)
{
	d->inertia = (t_vec2f){ length, 0.0 };
	actualize_dir(angle, &d->inertia);
}
