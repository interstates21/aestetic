/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_shoot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:03:45 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:04:08 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int		shoot(t_env *e)
{
	if (!e->player.shooting)
		return (0);
	e->player.shooting--;
	return (1);
}

void	update_ammo(t_env *e)
{
	int	ammo;

	ammo = e->weapon_type.current_ammo;
	if (!ammo)
		return ;
	e->weapon_type.current_ammo--;
}

int		check_last_anim(t_env *e)
{
	if (e->player.is_curr_anim == 5)
		if (!e->player.time_anim_weapon)
			return (true);
	return (false);
}

void	player_actions(t_env *e)
{
	int	ammo;

	ammo = e->weapon_type.current_ammo;
	if (shoot(e))
		ft_putstr("");
	else
		handle_click(e);
	if (check_last_anim(e))
	{
		update_ammo(e);
		create_projectile(e, e->weapon_type.left_projectile);
	}
}
