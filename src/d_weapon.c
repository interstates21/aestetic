/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_weapon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:08:20 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:30:25 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	display_weapon(t_env *d, SDL_Surface *s, t_vec2f start, t_vec2f end)
{
	t_vec2f		x_y;
	uint32_t	colo;

	x_y.x = start.x;
	while (x_y.x < end.x)
	{
		x_y.y = start.y;
		while (x_y.y < MIN(HEIGHT, end.y))
		{
			colo = pixel_pls(s, 100.0 / (end.x - start.x) * 0.01 *
				(x_y.x - start.x), 100.0 / (end.y - start.y) * 0.01 *
														(x_y.y - start.y), 0);
			colo = to_search_alpha(((uint32_t *)d->sdl.screen->pixels)
					[(short)x_y.x + (short)x_y.y * d->sdl.screen->w], colo);
			pixel_put(d, new_v3_proj(x_y.x, x_y.y), colo, 0);
			x_y.y++;
		}
		x_y.x++;
	}
}

void	displaing_weap(t_env *d)
{
	t_vec2f	start;
	t_vec2f	tmp;
	t_vec2	weap;
	t_vec2f	end;

	if (!d->player.time_anim_weapon)
		(d->player.is_curr_anim = d->player.anim_weap[d->player.
		curr_weap][d->player.is_curr_anim]) && (d->player.
		time_anim_weapon = d->player.anim_speed[d->player.curr_weap]);
	weap.x = d->weapon_tex[d->player.curr_weap]
		[d->player.is_curr_anim]->w;
	weap.y = d->weapon_tex[d->player.curr_weap]
		[d->player.is_curr_anim]->h;
	d->player.time_anim_weapon--;
	start.x = WIDTH * 0.5 + d->player.time_new_weapon * WIDTH * 0.003 -
	weap.x * 0.5 * SIZE_OF_WEAP;
	tmp = d->inertia;
	actualize_dir(d->cam.rot, &tmp);
	start.x -= tmp.x * 150;
	end.x = start.x + weap.x * SIZE_OF_WEAP;
	end.y = (HEIGHT + d->player.time_new_weapon *
		HEIGHT * 0.010 + MAX_INERTIA * 50) + tmp.y * 50;
	start.y = end.y - weap.y * SIZE_OF_WEAP;
	display_weapon(d, d->weapon_tex[d->player.curr_weap]
		[d->player.is_curr_anim], start, end);
}
