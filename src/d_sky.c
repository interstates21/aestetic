/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_sky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:08:35 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 22:09:40 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_sky(t_env *d, t_projdata *p, t_frustum *fr)
{
	SDL_Surface	*textures;
	t_vec2		v_h;
	t_vec2		x_y;

	if (p->neighbor && p->neighbor->outdoor)
		return ;
	textures = d->textures[p->sector->ceilpicnum];
	v_h.y = HEIGHT + MAX_Y_OFFSET * 2;
	x_y.x = p->cx1 - 1;
	while (++x_y.x <= p->cx2)
	{
		p->u = (unsigned int)(((double)x_y.x + d->cam.rot * 1000) /
				(WIDTH * (v_h.y / HEIGHT)) * textures->w) % textures->w;
		x_y.y = MIN(fr->ybottom[x_y.x], LERP(CLAMP(NORMALIZE(x_y.x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--x_y.y >= fr->ytop[x_y.x])
		{
			v_h.x = ((double)x_y.y + d->cam.y_offset + MAX_Y_OFFSET) /
															v_h.y * textures->h;
			pixel_put(d, new_v3(x_y.x, x_y.y, 0), ((uint32_t*)textures->
				pixels)[(int)p->u + v_h.x * textures->w], 0);
		}
	}
}
