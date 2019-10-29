/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:17:21 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:13:19 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		new_z_buff_and_put_collor(t_env *d, t_vec2 x_y, uint32_t colo,
															t_vec2f dist_mod)
{
	pixel_put(d, new_v3(x_y.x, x_y.y, 0), colo, 0);
	d->z_buff[x_y.x + x_y.y * d->sdl.screen->w] = dist_mod.x;
}

void		displaing_sprite(t_env *d, SDL_Surface *s,
		t_display_data disp_data, t_vec2f dist_mod)
{
	t_vec2		x_y;
	uint32_t	colo;

	x_y.x = disp_data.cut_start - 1;
	while (++x_y.x <= disp_data.cut_end)
	{
		x_y.y = dist_mod.y == 2 ? MAX(disp_data.ytop[x_y.x],
			disp_data.start.y) - 1 : MAX(0, disp_data.start.y) - 1;
		while (++x_y.y <= MIN(dist_mod.y == 2 ? disp_data.ybot[x_y.x] :
												HEIGHT - 1, disp_data.end.y))
		{
			if (dist_mod.x >= d->z_buff[x_y.x + x_y.y * d->sdl.screen->w]
														&& dist_mod.y < 2)
				continue;
			colo = pixel_pls(s, dist_mod.y == 0 ?
				1 - (disp_data.scale.x * (x_y.x - disp_data.start.x)) :
					disp_data.scale.x * (x_y.x - disp_data.start.x),
			disp_data.scale.y * (x_y.y - disp_data.start.y), 0);
			colo = to_search_alpha(((uint32_t *)d->sdl.screen->pixels)
					[x_y.x + x_y.y * d->sdl.screen->w], colo);
			if (colo != pixel_pls(d->sdl.screen, x_y.x, x_y.y, 2))
				new_z_buff_and_put_collor(d, x_y, shad(shd_fct(d, &d->
				sectors[disp_data.this_sect], dist_mod.x, 0), colo), dist_mod);
		}
	}
}
