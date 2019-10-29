/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_sky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:08:35 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 17:15:22 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	displaing_sky(t_env *d, t_proj_env *p, t_frustum *fr)
{
	SDL_Surface	*texts;
	t_vec2		v_h;
	t_vec2		x_y;

	if (p->portal && p->portal->outdoor)
		return ;
	texts = d->texts[p->sector->ceilpicnum];
	v_h.y = HEIGHT + MAX_Y_OFFSET * 2;
	x_y.x = p->cx1 - 1;
	while (++x_y.x <= p->cx2)
	{
		p->u = (unsigned int)(((double)x_y.x + d->cam.rot * 1000) /
				(WIDTH * (v_h.y / HEIGHT)) * texts->w) % texts->w;
		x_y.y = MIN(fr->ybottom[x_y.x], LERP(CLAMP(NORMALIZE(x_y.x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--x_y.y >= fr->ytop[x_y.x])
		{
			v_h.x = ((double)x_y.y + d->cam.y_offset + MAX_Y_OFFSET) /
															v_h.y * texts->h;
			pixel_put(d, new_v3(x_y.x, x_y.y, 0), ((uint32_t*)texts->
				pixels)[(int)p->u + v_h.x * texts->w], 0);
		}
	}
}
