/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_shoot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:03:45 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 03:08:27 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int	shoot(t_data *e) {
	if (!e->player.can_shoot)
		return (0);
	e->player.can_shoot--;
	return (1);
}


void update_ammo(t_data *e) {
    int ammo = e->weapon_type.current_ammo;

    if (!ammo)
        return ;
    e->weapon_type.current_ammo--;
}

int     check_last_anim(t_data *e) {
    if (e->player.current_anim_playing == 5)
        if (!e->player.timer_anim_weap)
            return (true);
    return (false);
}

void	player_actions(t_data *e)
{
    int ammo = e->weapon_type.current_ammo;
	if (shoot(e))
		ft_putstr("shoot ");
	else
        handle_click(e);
	if (check_last_anim(e))
	{
        update_ammo(e);
		create_projectile(e, e->weapon_type.left_projectile);
	}
}
