/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_ceil_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:04:20 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 17:15:46 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

/*
** bdeomin
*/

double	edge_function(t_vec3f a, t_vec3f b, int x, int y)
{
	return (x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x);
}

void	drawing_c_f(t_env *d, t_projdata *p, int mode, t_vec2 x_y)
{
	double		w[3];
	double		z;

	mode == 0 ? (w[0] = edge_function(p->a[1], p->a[2], x_y.x, x_y.y) /
																	p->areaa) :
			(w[0] = edge_function(p->v[1], p->v[2], x_y.x, x_y.y) / p->area);
	mode == 0 ? (w[1] = edge_function(p->a[2], p->a[0], x_y.x, x_y.y) /
																	p->areaa) :
			(w[1] = edge_function(p->v[2], p->v[0], x_y.x, x_y.y) / p->area);
	mode == 0 ? (w[2] = edge_function(p->a[0], p->a[1], x_y.x, x_y.y) /
																	p->areaa) :
			(w[2] = edge_function(p->v[0], p->v[1], x_y.x, x_y.y) / p->area);
	mode == 0 ? (z = 1 / (w[0] * p->a[0].z + w[1] * p->a[1].z + w[2] *
																p->a[2].z)) :
			(z = 1 / (w[0] * p->v[0].z + w[1] * p->v[1].z + w[2] * p->v[2].z));
	if (z <= d->zbuffer[x_y.x + x_y.y * WIDTH])
		pixel_put(d, new_v3(x_y.x, x_y.y, z), shade(shd_fct(d, p->sector, z, 1),
			pixel_pls(d->texts[mode == 0 ? p->sector->ceilpicnum :
				p->sector->floorpicnum], mode == 0 ?
				((w[0] * p->b[0].x + w[1] * p->b[1].x + w[2] * p->b[2].x) * z) :
				((w[0] * p->c[0].x + w[1] * p->c[1].x + w[2] * p->c[2].x) * z),
				mode == 0 ? ((w[0] * p->b[0].z + w[1] * p->b[1].z + w[2] *
					p->b[2].z) * z) :
					((w[0] * p->c[0].z + w[1] * p->c[1].z + w[2] *
					p->c[2].z) * z), 1)), 1);
}

void	displaing_cl_fl(t_env *d, t_projdata *p, t_frustum *fr, int mode)
{
	t_vec2		x_y;

	x_y.x = p->cx1 - 1;
	while (++x_y.x <= p->cx2)
	{
		mode == 0 ? (x_y.y = MIN(fr->ybottom[x_y.x], LERP(CLAMP(NORMALIZE(x_y.x,
			p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1) :
					(x_y.y = MAX(fr->ytop[x_y.x], LERP(CLAMP(NORMALIZE(x_y.x,
			p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1);
		while (mode == 0 ? (--x_y.y >= fr->ytop[x_y.x]) :
												(++x_y.y <= fr->ybottom[x_y.x]))
			drawing_c_f(d, p, mode, x_y);
	}
}
