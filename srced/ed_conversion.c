#include "editor.h"

t_vec2f	worldtoscreen(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - d->pos.x) * d->scale + W / 2,
			-(p.y - d->pos.y) * d->scale + H / 2});
}

t_vec2f	screentoworld(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - W / 2) / d->scale + d->pos.x,
			-(p.y - H / 2) / d->scale + d->pos.y});
}

t_vec2f	v2_plus(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x + v2.x, v1.y + v2.y});
}

double	v2_len(t_vec2f v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}
