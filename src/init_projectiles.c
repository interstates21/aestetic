/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projectiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:30:39 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 17:26:18 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	init_proj(t_env *d)
{
	d->anim_rot_type[FIREBALL_1].threat_to_monster = false;
	d->anim_rot_type[FIREBALL_1].threat_to_player = true;
	d->anim_rot_type[FIREBALL_1].hitbox_radius = 0.5;
	d->anim_rot_type[FIREBALL_1].speed = 0.05;
	d->anim_rot_type[FIREBALL_1].damage = 20;
	d->anim_rot_type[FIREBALL_1].size = 12;
	d->anim_rot_type[CRYO_BALLISTA].threat_to_player = false;
	d->anim_rot_type[CRYO_BALLISTA].threat_to_monster = true;
	d->anim_rot_type[CRYO_BALLISTA].hitbox_radius = 0.1;
	d->anim_rot_type[CRYO_BALLISTA].speed = 0.25;
	d->anim_rot_type[CRYO_BALLISTA].damage = 80;
	d->anim_rot_type[CRYO_BALLISTA].size = 1.5;
}

void	init_projectiles_type_cryo_bow(t_env *d)
{
	int i;

	i = 0;
	while (i < 19)
	{
		(i == 6) ? d->anim_rot_type[CRYO_BALLISTA].anim_order[i++] = 6 : 0;
		d->anim_rot_type[CRYO_BALLISTA].anim_order[i] = i + 1;
		i++;
	}
	d->anim_rot_type[CRYO_BALLISTA].anim_order[19] = MUST_BE_DESTROYED;
	d->anim_rot_type[CRYO_BALLISTA].anim_order[COLLISION_ID] = 7;
}

void	init_projectiles_fireball_1(t_env *d)
{
	d->anim_rot_type[FIREBALL_1].anim_order[0] = 1;
	d->anim_rot_type[FIREBALL_1].anim_order[1] = 0;
	d->anim_rot_type[FIREBALL_1].anim_order[COLLISION_ID] = 2;
	d->anim_rot_type[FIREBALL_1].anim_order[2] = 3;
	d->anim_rot_type[FIREBALL_1].anim_order[3] = 4;
	d->anim_rot_type[FIREBALL_1].anim_order[4] = MUST_BE_DESTROYED;
}

void	init_weapons(t_env *d)
{
	d->weapon_type.rate_of_fire[0] =
		d->player.anim_speed[CRYO_BALLISTA] * 11;
	d->weapon_type.has_alt_fire = false;
}

void	proj_initialization(t_env *d)
{
	ft_bzero(d->anim_rot_type, sizeof(t_anim_rot_type) * N_ANIM_ROT_TYPES);
	ft_bzero(d->anim_rots, sizeof(t_anim_rot) * N_ANIM_ROTS);
	init_weapons(d);
	init_proj(d);
	init_projectiles_type_cryo_bow(d);
	init_projectiles_fireball_1(d);
}
