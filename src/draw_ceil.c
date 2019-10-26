/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:08:35 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 21:40:35 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_sky(t_data *d, t_projdata *p, t_frustum *fr)
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

void	proj_ceil_or_floor(t_data *d, t_projdata *p, int mode)
{
	mode == 0 ? (p->b[0] = transform_back(d, new_v3(-1, 0, 1))) :
				(p->c[0] = transform_back(d, new_v3(-1, 0, 1)));
	mode == 0 ? (p->b[1] = transform_back(d, new_v3(1, 0, 1))) :
				(p->c[1] = transform_back(d, new_v3(1, 0, 1)));
	mode == 0 ? (p->b[2] = transform_back(d, new_v3z(2))) :
				(p->c[2] = transform_back(d, new_v3z(2)));
	mode == 0 ? (p->a[0] = new_v3(-WIDTH + WIDTH / 2, get_ceildh(d,
		p->sector, v3_to_v2(p->b[0])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset),
		1)) : (p->v[0] = new_v3(-WIDTH + WIDTH / 2, get_floordh(d, p->sector,
		v3_to_v2(p->c[0])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset), 1));
	mode == 0 ? (p->a[1] = new_v3(WIDTH + WIDTH / 2, get_ceildh(d,
		p->sector, v3_to_v2(p->b[1])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset),
		1)) : (p->v[1] = new_v3(WIDTH + WIDTH / 2, get_floordh(d, p->sector,
		v3_to_v2(p->c[1])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset), 1));
	mode == 0 ? (p->a[2] = new_v3(WIDTH / 2, get_ceildh(d, p->sector,
		v3_to_v2(p->b[2])) * -WIDTH * 0.5 + (HEIGHT / 2 - d->cam.y_offset),
		0.5)) : (p->v[2] = new_v3(WIDTH / 2, get_floordh(d, p->sector,
		v3_to_v2(p->c[2])) * -WIDTH * 0.5 + (HEIGHT / 2 - d->cam.y_offset),
		0.5));
	mode == 0 ? (p->b[2].x /= 2) : (p->c[2].x /= 2);
	mode == 0 ? (p->b[2].z /= 2) : (p->c[2].z /= 2);
	mode == 0 ? (p->areaa = edge_function(p->a[0], p->a[1],
												p->a[2].x, p->a[2].y)) :
		(p->area = edge_function(p->v[0], p->v[1], p->v[2].x, p->v[2].y));
}

void	*draw_ceil_thread(void *void_arg)
{
	t_thread_arg	*arg;

	arg = (t_thread_arg*)void_arg;
	if (!arg->p->sector->outdoor)
		draw_ceil_floor(arg->d, arg->p, arg->fr, 0);
	else
		draw_sky(arg->d, arg->p, arg->fr);
	return (NULL);
}
