#include "../includes/doom_nukem.h"

bool	set_pos_m16_inside_sec(t_data *d, int16_t id, t_vec2f *pos)
{
	*pos = d->monsters[id].pos;
	pos->x -= d->cam.pos.x;
	pos->y -= d->cam.pos.z;
	actualize_dir(d->cam.rot, pos);
	return (true);
}
