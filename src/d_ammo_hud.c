/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_ammo_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:34:28 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:16:38 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	displaing_ammo(t_env *d, t_weapon_type weapon_type)
{
	static char buf[100] = "Ammo: ";
	static char buf2[100] = "Health: ";

	ft_strcpy(buf + 6, new_itoa_fun(weapon_type.current_ammo));
	ft_strcpy(buf + ft_strlen(buf), " / ");
	ft_strcpy(buf + ft_strlen(buf), new_itoa_fun(MAX_BULLETS));
	displaing_str(d, (t_font){buf, 50, 80, 0, 2});
	ft_strcpy(buf2 + 8, new_itoa_fun(d->player.health));
	displaing_str(d, (t_font){buf2, 50, 50, 0, 2});
}
