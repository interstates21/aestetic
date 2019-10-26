/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 23:10:02 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/25 22:23:43 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	draw_ammo(t_data *d, t_weapon_type weapon_type)
{
	static char buf[100] = "Ammo: ";
	static char buf2[100] = "Health: ";

	ft_strcpy(buf + 6, ft_itoa_static(weapon_type.current_ammo));
	ft_strcpy(buf + ft_strlen(buf), " / ");
	ft_strcpy(buf + ft_strlen(buf), ft_itoa_static(MAX_BULLETS));
	draw_string(d, (t_font){buf, 50, 80, 0, 2});
	ft_strcpy(buf2 + 8, ft_itoa_static(d->player.health));
	draw_string(d, (t_font){buf2, 50, 50, 0, 2});
}

static void	draw_fuel(t_data *d)
{
	static char buf[100] = "Fuel: ";

	ft_strcpy(buf + 6, ft_itoa_static(d->player.is_flying));
	draw_string(d, (t_font){buf, 50, 110, 0, 2});
}

static void	draw_timed_msg(t_data *d)
{
	if (!d->msg[0])
		return ;
	draw_string(d, (t_font){d->msg, 50, HEIGHT - 180, 0, 2});
	if (SDL_GetTicks() - d->msg_start > 3000)
		d->msg[0] = 0;
}

void		draw_hud(t_data *d)
{
	draw_timed_msg(d);
	draw_ammo(d, d->weapon_type);
	if (d->player.is_flying)
		draw_fuel(d);
}
