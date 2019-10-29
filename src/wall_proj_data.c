/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_proj_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:03:59 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:15:07 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int		new_proj_data(t_proj_env *p, t_frustum *fr, int mode)
{
	if (mode == 0)
	{
		p->u1 /= p->z1;
		p->u2 /= p->z2;
		p->z1 = 1 / p->z1;
		p->z2 = 1 / p->z2;
		p->cx1 = MAX(p->x1, fr->x1);
		p->cx2 = MIN(p->x2, fr->x2);
		p->x = p->cx1 - 1;
	}
	else
	{
		p->n = CLAMP(NORMALIZE(p->x, p->x1, p->x2), 0, 1);
		p->z = 1 / LERP(p->n, p->z1, p->z2);
		p->u = LERP(p->n, p->u1, p->u2) * p->z;
		if (p->z >= p->z_buff[p->x] && mode == 1)
			return (1);
		mode == 1 ? ((p->z_buff[p->x] = p->z) &&
				(p->visibility_buf[p->x] = true)) : true;
		p->ya = LERP(p->n, p->y1a, p->y2a);
		p->yb = LERP(p->n, p->y1b, p->y2b);
		p->yc = LERP(p->n, p->y1c, p->y2c);
		p->yd = LERP(p->n, p->y1d, p->y2d);
	}
	return (0);
}

int		new_proj_data2(t_env *d, t_proj_env *p, t_frustum *fr, int mode)
{
	if (mode <= 1)
	{
		p->nya = LERP(p->n, p->ny1a, p->ny2a);
		p->nyb = LERP(p->n, p->ny1b, p->ny2b);
		(p->wall->is_door && mode == 0) ?
			((p->nya = MAX(p->nya, p->ya)) &&
			(p->nyb = MIN(p->nyb, p->yb))) : true;
		p->door_begin = MIN(mode == 0 ? p->yb : p->yd, p->nyb);
		p->door_h = p->door_begin - p->yc;
		p->nya += (p->door_begin - MAX(p->yc, p->nya)) *
			(1 - d->door_active[p->wall - d->walls]);
	}
	else
	{
		p->tex = d->texts[mode == 4 ? p->wall->lowerpicnum :
											p->wall->middlepicnum];
		p->u_tex = (p->u - floor(p->u)) * p->tex->w;
		mode < 4 ? p->shadefactor = shd_fct(d, p->sector, p->z, 1) : true;
		if (mode == 2 || mode == 4)
			p->y = MAX(fr->ytop[p->x], mode == 4 ? p->nyb : p->ya) - 1;
		else
			return (fr->ytop[p->x]);
	}
	return (0);
}
