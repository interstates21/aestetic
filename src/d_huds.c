/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_huds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:35:57 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 22:42:21 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

/*
** bdeomin
*/

void	draw_timed_msg(t_env *d)
{
	if (!d->msg[0])
		return ;
	draw_string(d, (t_font){d->msg, 50, HEIGHT - 180, 0, 2});
	if (SDL_GetTicks() - d->msg_start > 3000)
		d->msg[0] = 0;
}

void	draw_hud(t_env *d)
{
	if (d->slot3)
		draw_inventory_slot(d, d->assets_texture[d->slot3->picnum],
				140, HEIGHT - 100);
	draw_timed_msg(d);
	draw_ammo(d, d->weapon_type);
	if (d->player.is_flying)
		draw_fuel(d);
}
