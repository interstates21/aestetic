/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_wall2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:04:06 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:13:19 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	drawing_wall(t_vec2 y_value, t_env *d, t_proj_env *p, int mode)
{
	uint32_t	pix;

	while (++y_value.x <= y_value.y)
	{
		pix = pixel_pls(p->tex, p->u_tex, (!p->wall->is_door || mode == 1) ?
				NORMALIZE(y_value.x, p->yc, p->yd) * p->y_scale :
				NORMALIZE(y_value.x, p->nya - p->door_h, p->nya), 3);
		if (mode == 0 || (pix >> 24) == 0xff)
			pixel_put(d, new_v3(p->x, y_value.x, p->z),
					shad(p->shadefactor, pix), 1);
	}
}

void	displaing_to_transp_wall(t_env *d, t_proj_env *p, t_frustum *fr)
{
	new_proj_data(p, fr, 2);
	if (p->portal)
		new_proj_data2(d, p, fr, 1);
	drawing_wall((t_vec2){new_proj_data2(d, p, fr, 3), fr->ybottom[p->x]},
																	d, p, 1);
}

void	displaing_n_wall(t_env *d, t_proj_env *p, t_frustum *fr)
{
	drawing_wall((t_vec2){p->y, MIN(fr->ybottom[p->x], p->nya)}, d, p, 0);
	new_proj_data2(d, p, fr, 4);
	drawing_wall((t_vec2){p->y, MIN(fr->ybottom[p->x], p->yb)}, d, p, 1);
}

void	displaing_no_n_wall(t_env *d, t_proj_env *p, t_frustum *fr)
{
	uint32_t px;

	while (++p->y <= MIN(fr->ybottom[p->x], p->yb))
		if (p->wall->posterpicnum >= 0 &&
			p->y > p->ya_poster && p->y < p->yb_poster && (((px =
			pixel_pls(p->poster, p->u_poster, NORMALIZE(p->y, p->ya_poster,
			p->yb_poster), 3)) >> 24) > 128))
			pixel_put(d, new_v3(p->x, p->y, p->z),
												shad(p->shadefactor, px),
																			1);
		else
			pixel_put(d, new_v3(p->x, p->y, p->z), shad(p->shadefactor,
						pixel_pls(p->tex, p->u_tex,
							NORMALIZE(p->y, p->yc, p->yd) * p->y_scale, 3)), 1);
}
