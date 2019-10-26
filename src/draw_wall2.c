/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:04:06 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/25 22:25:35 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_wall_transparent(t_data *d, t_projdata *p, t_frustum *fr)
{
	new_proj_data(p, fr, 2);
	if (p->neighbor)
		new_proj_data2(d, p, fr, 1);
	drawing_wall((t_vec2){new_proj_data2(d, p, fr, 3), fr->ybottom[p->x]},
																	d, p, 1);
}

void	draw_wall3(t_data *d, t_projdata *p, t_frustum *nfr, bool *visible)
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

void	draw_wall_no_nei(t_data *d, t_projdata *p, t_frustum *fr)
{
	uint32_t px;

	while (++p->y <= MIN(fr->ybottom[p->x], p->yb))
		if (p->wall->posterpicnum >= 0 &&
			p->y > p->ya_poster && p->y < p->yb_poster && (((px =
			pixel_pls(p->poster, p->u_poster, NORMALIZE(p->y, p->ya_poster,
			p->yb_poster), 3)) >> 24) > 128))
			putpixel2(d, p->z, (t_vec2){p->x, p->y}, shade(p->shadefactor, px));
		else
			putpixel2(d, p->z, (t_vec2){p->x, p->y}, shade(p->shadefactor,
						pixel_pls(p->tex, p->u_tex,
							NORMALIZE(p->y, p->yc, p->yd) * p->y_scale, 3)));
}

void	drawing_wall(t_vec2 y_value, t_data *d, t_projdata *p, int mode)
{
	uint32_t	pix;

	while (++y_value.x <= y_value.y)
	{
		pix = pixel_pls(p->tex, p->u_tex, (!p->wall->is_door || mode == 1) ?
				NORMALIZE(y_value.x, p->yc, p->yd) * p->y_scale :
				NORMALIZE(y_value.x, p->nya - p->doorheight, p->nya), 3);
		if (mode == 0 || (pix >> 24) == 0xff)
			putpixel2(d, p->z, (t_vec2){p->x, y_value.x},
					shade(p->shadefactor, pix));
	}
}

int		new_proj_data2(t_data *d, t_projdata *p, t_frustum *fr, int mode)
{
	if (mode <= 1)
	{
		p->nya = LERP(p->n, p->ny1a, p->ny2a);
		p->nyb = LERP(p->n, p->ny1b, p->ny2b);
		(p->wall->is_door && mode == 0) ?
			((p->nya = MAX(p->nya, p->ya)) &&
			(p->nyb = MIN(p->nyb, p->yb))) : true;
		p->doorbottom = MIN(mode == 0 ? p->yb : p->yd, p->nyb);
		p->doorheight = p->doorbottom - p->yc;
		p->nya += (p->doorbottom - MAX(p->yc, p->nya)) *
			(1 - d->doorstate[p->wall - d->walls]);
	}
	else
	{
		p->tex = d->textures[mode == 4 ? p->wall->lowerpicnum :
											p->wall->middlepicnum];
		p->u_tex = (p->u - floor(p->u)) * p->tex->w;
		mode < 4 ? p->shadefactor = getshadefactor(d, p, p->z) : true;
		if (mode == 2 || mode == 4)
			p->y = MAX(fr->ytop[p->x], mode == 4 ? p->nyb : p->ya) - 1;
		else
			return (fr->ytop[p->x]);
	}
	return (0);
}
