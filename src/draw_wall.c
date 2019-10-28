/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 23:02:51 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 18:26:50 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

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
	new_proj_data2(d, p, fr, 2);
	if (!p->neighbor)
		draw_wall_no_nei(d, p, fr);
	else if (p->neighbor)
		draw_wall_nei(d, p, fr);
}

void	draw_wall4(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	new_proj_data2(d, p, fr, 0);
	nfr->ytop[p->x] = CLAMP((p->sector->outdoor && p->neighbor->outdoor) ?
			0 : p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
	nfr->ybottom[p->x] = CLAMP(p->nyb, fr->ytop[p->x],
			fr->ybottom[p->x]);
	if (p->sector->outdoor && p->neighbor->outdoor)
		p->ya = p->nya;
}

void	draw_wall2(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	if (new_proj_data(p, fr, 1))
		return ((void)(p->visible[p->x] = false));
	if (p->neighbor)
		draw_wall4(d, p, fr, nfr);
	draw_wall2bis(d, p, fr);
}

int		new_proj_data(t_projdata *p, t_frustum *fr, int mode)
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
		if (p->z >= p->zbuffer[p->x] && mode == 1)
			return (1);
		mode == 1 ? ((p->zbuffer[p->x] = p->z) &&
				(p->visible[p->x] = true)) : true;
		p->ya = LERP(p->n, p->y1a, p->y2a);
		p->yb = LERP(p->n, p->y1b, p->y2b);
		p->yc = LERP(p->n, p->y1c, p->y2c);
		p->yd = LERP(p->n, p->y1d, p->y2d);
	}
	return (0);
}

void	draw_wall(t_data *d, t_projdata *p, t_frustum *fr)
{
	t_frustum	new_fr;

	if (p->neighbor && fr->visitedportals[p->wall - d->walls])
		return ;
	if (p->neighbor)
	{
		new_fr = *fr;
		new_fr.visitedportals[p->wall - d->walls] = true;
	}
	new_proj_data(p, fr, 0);
	while (++p->x <= p->cx2)
		draw_wall2(d, p, fr, &new_fr);
	draw_wall3(d, p, &new_fr, p->visible);
	if (p->neighbor && p->wall->is_transparent)
	{
		p->x = MAX(p->x1, new_fr.x1);
		while (++p->x <= MIN(p->x2, new_fr.x2))
			draw_wall_transparent(d, p, &new_fr);
	}
}
