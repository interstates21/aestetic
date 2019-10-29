/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_ceil_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:04:20 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:13:19 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

double	fun_to_edget(t_vec3f a, t_vec3f b, int x, int y)
{
	return (x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x);
}

void	drawing_c_f(t_env *d, t_proj_env *p, int mode, t_vec2 v)
{
	double		w[3];
	double		z;

	mode == 0 ? (w[0] = fun_to_edget(p->a[1], p->a[2], v.x, v.y) /
																	p->areaa) :
			(w[0] = fun_to_edget(p->v[1], p->v[2], v.x, v.y) / p->area);
	mode == 0 ? (w[1] = fun_to_edget(p->a[2], p->a[0], v.x, v.y) /
																	p->areaa) :
			(w[1] = fun_to_edget(p->v[2], p->v[0], v.x, v.y) / p->area);
	mode == 0 ? (w[2] = fun_to_edget(p->a[0], p->a[1], v.x, v.y) /
																	p->areaa) :
			(w[2] = fun_to_edget(p->v[0], p->v[1], v.x, v.y) / p->area);
	mode == 0 ? (z = 1 / (w[0] * p->a[0].z + w[1] * p->a[1].z + w[2] *
																p->a[2].z)) :
			(z = 1 / (w[0] * p->v[0].z + w[1] * p->v[1].z + w[2] * p->v[2].z));
	if (z <= d->z_buff[v.x + v.y * WIDTH])
		pixel_put(d, new_v3(v.x, v.y, z), shad(shd_fct(d, p->sector, z, 1),
			pixel_pls(d->texts[mode == 0 ? p->sector->ceilpicnum :
				p->sector->floorpicnum], mode == 0 ?
				((w[0] * p->b[0].x + w[1] * p->b[1].x + w[2] * p->b[2].x) * z) :
				((w[0] * p->c[0].x + w[1] * p->c[1].x + w[2] * p->c[2].x) * z),
				mode == 0 ? ((w[0] * p->b[0].z + w[1] * p->b[1].z + w[2] *
					p->b[2].z) * z) :
					((w[0] * p->c[0].z + w[1] * p->c[1].z + w[2] *
					p->c[2].z) * z), 1)), 1);
}

void	displaing_cl_fl(t_env *d, t_proj_env *p, t_frustum *fr, int mode)
{
	t_vec2		v;

	v.x = p->cx1 - 1;
	while (++v.x <= p->cx2)
	{
		mode == 0 ? (v.y = MIN(fr->ybottom[v.x], LERP(CLAMP(NORMALIZE(v.x,
			p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1) :
					(v.y = MAX(fr->ytop[v.x], LERP(CLAMP(NORMALIZE(v.x,
			p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1);
		while (mode == 0 ? (--v.y >= fr->ytop[v.x]) :
												(++v.y <= fr->ybottom[v.x]))
			drawing_c_f(d, p, mode, v);
	}
}
