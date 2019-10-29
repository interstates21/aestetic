/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_wall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:08:20 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:14:05 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_wall4(t_env *d, t_proj_env *p, t_frustum *fr, t_frustum *nfr)
{
	new_proj_data2(d, p, fr, 0);
	nfr->ytop[p->x] = CLAMP((p->sector->outdoor && p->portal->outdoor) ?
			0 : p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
	nfr->ybottom[p->x] = CLAMP(p->nyb, fr->ytop[p->x],
			fr->ybottom[p->x]);
	if (p->sector->outdoor && p->portal->outdoor)
		p->ya = p->nya;
}

void	draw_wall3(t_env *d, t_proj_env *p, t_frustum *nfr,
														bool *visibility_buf)
{
	int	end;

	if (p->cx2 - p->cx1 <= 2)
		return ;
	end = p->cx2;
	while (!visibility_buf[p->cx1] && p->cx1 < end)
		(p->cx1)++;
	p->cx2--;
	if (p->cx1 >= end)
		return ;
	p->cx2 = p->cx1;
	while (visibility_buf[p->cx2] && p->cx2 < end)
		p->cx2++;
	if (p->portal && p->cx1 < p->cx2)
	{
		nfr->x1 = p->cx1;
		nfr->x2 = p->cx2;
		sect_rendering(d, p->portal, nfr);
	}
}

void	draw_wall2(t_env *d, t_proj_env *p, t_frustum *fr, t_frustum *nfr)
{
	if (new_proj_data(p, fr, 1))
		return ((void)(p->visibility_buf[p->x] = false));
	if (p->portal)
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
	if (!p->portal)
		displaing_no_n_wall(d, p, fr);
	else if (p->portal)
		displaing_n_wall(d, p, fr);
}

void	displaing_wall(t_env *d, t_proj_env *p, t_frustum *fr)
{
	t_frustum	new_fr;

	if (p->portal && fr->visitedportals[p->wall - d->walls])
		return ;
	if (p->portal)
	{
		new_fr = *fr;
		new_fr.visitedportals[p->wall - d->walls] = true;
	}
	new_proj_data(p, fr, 0);
	while (++p->x <= p->cx2)
		draw_wall2(d, p, fr, &new_fr);
	draw_wall3(d, p, &new_fr, p->visibility_buf);
	if (p->portal && p->wall->is_transparent)
	{
		p->x = MAX(p->x1, new_fr.x1);
		while (++p->x <= MIN(p->x2, new_fr.x2))
			displaing_to_transp_wall(d, p, &new_fr);
	}
}
