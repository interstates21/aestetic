/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_huds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:35:57 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:16:54 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_timed_msg(t_env *d)
{
	if (!d->msg[0])
		return ;
	displaing_str(d, (t_font){d->msg, 50, HEIGHT - 180, 0, 2});
	if (SDL_GetTicks() - d->msg_start > 3000)
		d->msg[0] = 0;
}

void	displaing_huds(t_env *d)
{
	if (d->slot3)
		displaing_invent(d, d->assets_texture[d->slot3->picnum],
				140, HEIGHT - 100);
	draw_timed_msg(d);
	displaing_ammo(d, d->weapon_type);
	if (d->player.flying)
		displaing_fuel(d);
}
