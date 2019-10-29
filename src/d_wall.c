/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_wall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:08:20 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:38:51 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

/*
** bdeomin
*/

void	draw_wall4(t_env *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	new_proj_data2(d, p, fr, 0);
	nfr->ytop[p->x] = CLAMP((p->sector->outdoor && p->neighbor->outdoor) ?
			0 : p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
	nfr->ybottom[p->x] = CLAMP(p->nyb, fr->ytop[p->x],
			fr->ybottom[p->x]);
	if (p->sector->outdoor && p->neighbor->outdoor)
		p->ya = p->nya;
}

void	draw_wall3(t_env *d, t_projdata *p, t_frustum *nfr, bool *visible)
{
	int	end;

	if (p->cx2 - p->cx1 <= 2)
		return ;
	end = p->cx2;
	while (!visible[p->cx1] && p->cx1 < end)
		(p->cx1)++;
	p->cx2--;
	if (p->cx1 >= end)
		return ;
	p->cx2 = p->cx1;
	while (visible[p->cx2] && p->cx2 < end)
		p->cx2++;
	if (p->neighbor && p->cx1 < p->cx2)
	{
		nfr->x1 = p->cx1;
		nfr->x2 = p->cx2;
		render_sector(d, p->neighbor, nfr);
	}
}

void	draw_wall2(t_env *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	if (new_proj_data(p, fr, 1))
		return ((void)(p->visible[p->x] = false));
	if (p->neighbor)
		draw_wall4(d, p, fr, nfr);
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
		displaing_n_wall(d, p, fr);
}

void	draw_wall(t_env *d, t_projdata *p, t_frustum *fr)
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
