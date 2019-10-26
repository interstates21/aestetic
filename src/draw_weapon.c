/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:08:20 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 21:41:57 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	display_weapon(t_data *d, SDL_Surface *s, t_vec2f start, t_vec2f end)
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
			colo = alpha(((uint32_t *)d->sdl.screen->pixels)
					[(short)x_y.x + (short)x_y.y * d->sdl.screen->w], colo);
			pixel_put(d, (t_vec3f){x_y.x, x_y.y, 0}, colo, 0);
			x_y.y++;
		}
		x_y.x++;
	}
}

void	draw_weapon2(t_data *d, t_vec2f start, t_vec2f tmp, t_vec2 weap_size)
{
	t_vec2f			end;

	end.x = start.x + weap_size.x * SIZE_OF_WEAP;
	end.y = (HEIGHT + d->player.timer_change_weap *
		HEIGHT * 0.010 + MAX_INERTIA * 50) + tmp.y * 50;
	start.y = end.y - weap_size.y * SIZE_OF_WEAP;
	display_weapon(d, d->weapon_tex[d->player.current_weapon]
		[d->player.current_anim_playing], start, end);
}

void	draw_weapon(t_data *d)
{
	t_vec2f			start;
	t_vec2f			tmp;
	int				weap_w;
	int				weap_h;

	if (!d->player.timer_anim_weap)
	{
		d->player.current_anim_playing = d->player.weapon_anim
		[d->player.current_weapon][d->player.current_anim_playing];
		d->player.timer_anim_weap =
			d->player.speed_anim[d->player.current_weapon];
	}
	weap_w = d->weapon_tex[d->player.current_weapon]
		[d->player.current_anim_playing]->w;
	weap_h = d->weapon_tex[d->player.current_weapon]
		[d->player.current_anim_playing]->h;
	d->player.timer_anim_weap--;
	start.x = WIDTH * 0.5 + d->player.timer_change_weap * WIDTH * 0.003 -
	weap_w * 0.5 * SIZE_OF_WEAP;
	tmp = d->inertia;
	actualize_dir(d->cam.rot, &tmp);
	start.x -= tmp.x * 150;
	draw_weapon2(d, start, tmp, (t_vec2){weap_w, weap_h});
}
