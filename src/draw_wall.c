/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 23:02:51 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/23 23:03:22 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_wall_nei(t_data *d, t_projdata *p, t_frustum *fr)
{
	while (++p->y <= MIN(fr->ybottom[p->x], p->nya))
		putpixel2(d, p->z, (t_vec2){p->x, p->y},
			shade(p->shadefactor, getpixel4(p->tex, p->u_tex, p->wall->is_door ?
				NORMALIZE(p->y, p->nya - p->doorheight, p->nya) :
				NORMALIZE(p->y, p->yc, p->yd) * p->y_scale)));
	p->tex = d->textures[p->wall->lowerpicnum];
	p->u_tex = (p->u - floor(p->u)) * p->tex->w;
	p->y = MAX(fr->ytop[p->x], p->nyb) - 1;
	while (++p->y <= MIN(fr->ybottom[p->x], p->yb))
		putpixel2(d, p->z, (t_vec2){p->x, p->y}, shade(p->shadefactor,
			getpixel4(p->tex, p->u_tex,
				NORMALIZE(p->y, p->yc, p->yd) * p->y_scale)));
}

void	draw_wall2bis(t_data *d, t_projdata *p, t_frustum *fr)
{
	p->ya_poster = 0;
	p->yb_poster = 0;
	if (p->wall->posterpicnum >= 0 && p->u > p->u1_poster &&
			p->u < p->u2_poster)
	{
		p->poster = d->posters[p->wall->posterpicnum];
		p->u_poster = (unsigned int)(NORMALIZE(p->u, p->u1_poster,
								p->u2_poster) * p->poster->w) % p->poster->w;
		p->margin = (double)(p->yd - p->yc) * (1.0 - p->poster_h) / 2.0;
		p->ya_poster = p->yc + p->margin;
		p->yb_poster = p->yd - p->margin;
	}
	p->tex = d->textures[p->wall->middlepicnum];
	p->u_tex = (p->u - floor(p->u)) * p->tex->w;
	p->y = MAX(fr->ytop[p->x], p->ya) - 1;
	p->shadefactor = getshadefactor(d, p, p->z);
	if (!p->neighbor)
		draw_wall_no_nei(d, p, fr);
	else if (p->neighbor)
		draw_wall_nei(d, p, fr);
}

void	draw_wall4(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->nya = LERP(p->n, p->ny1a, p->ny2a);
	p->nyb = LERP(p->n, p->ny1b, p->ny2b);
	if (p->wall->is_door)
	{
		p->nya = MAX(p->nya, p->ya);
		p->nyb = MIN(p->nyb, p->yb);
	}
	p->doorbottom = MIN(p->yb, p->nyb);
	p->doorheight = p->doorbottom - p->yc;
	p->nya += (p->doorbottom - MAX(p->yc, p->nya)) *
		(1 - d->doorstate[p->wall - d->walls]);
	nfr->ytop[p->x] = CLAMP((p->sector->outdoor && p->neighbor->outdoor) ?
			0 : p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
	nfr->ybottom[p->x] = CLAMP(p->nyb, fr->ytop[p->x],
			fr->ybottom[p->x]);
	if (p->sector->outdoor && p->neighbor->outdoor)
		p->ya = p->nya;
}

void	draw_wall2(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->n = CLAMP(NORMALIZE(p->x, p->x1, p->x2), 0, 1);
	p->z = 1 / LERP(p->n, p->z1, p->z2);
	p->u = LERP(p->n, p->u1, p->u2) * p->z;
	if (p->z >= p->zbuffer[p->x])
		return ((void)(p->visible[p->x] = false));
	p->zbuffer[p->x] = p->z;
	p->visible[p->x] = true;
	p->ya = LERP(p->n, p->y1a, p->y2a);
	p->yb = LERP(p->n, p->y1b, p->y2b);
	p->yc = LERP(p->n, p->y1c, p->y2c);
	p->yd = LERP(p->n, p->y1d, p->y2d);
	if (p->neighbor)
		draw_wall4(d, p, fr, nfr);
	draw_wall2bis(d, p, fr);
}

void	draw_wall(t_data *d, t_projdata *p, t_frustum *fr)
{
	t_frustum	nfr;

	if (p->neighbor && fr->visitedportals[p->wall - d->walls])
		return ;
	if (p->neighbor)
	{
		nfr = *fr;
		nfr.visitedportals[p->wall - d->walls] = true;
	}
	p->u1 /= p->z1;
	p->u2 /= p->z2;
	p->z1 = 1 / p->z1;
	p->z2 = 1 / p->z2;
	p->cx1 = MAX(p->x1, fr->x1);
	p->cx2 = MIN(p->x2, fr->x2);
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
		draw_wall2(d, p, fr, &nfr);
	draw_wall3(d, p, &nfr, p->visible);
	if (p->neighbor && p->wall->is_transparent)
	{
		p->x = MAX(p->x1, nfr.x1);
		while (++p->x <= MIN(p->x2, nfr.x2))
			draw_wall_transparent(d, p, &nfr);
	}
}
