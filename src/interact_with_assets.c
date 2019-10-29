/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_assets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:43:27 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:27:34 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static bool	check_if_return(t_env *d, t_objects *asset)
{
	if (d->player.health == 100 && asset->stat_mod.heal)
		return (true);
	if (d->weapon_type.current_ammo == MAX_BULLETS &&
										asset->stat_mod.ballista_ammo)
		return (true);
	return (false);
}

static bool	check_jetpack(t_env *d, t_objects *asset)
{
	if (asset->stat_mod.ballista_ammo)
		play_sound(d, AMMO_SOUND, v3_to_v2(d->cam.pos));
	if (asset->is_key)
	{
		if (!d->slot3)
			d->slot3 = asset;
		else
			return (false);
	}
	else if (asset->is_jetpack && (!d->slot3 || d->slot3->is_jetpack))
		d->slot3 = asset;
	else if (asset->is_jetpack)
		return (false);
	if (asset->is_jetpack)
		d->player.flying = MIN(d->player.flying + FUEL, MAX_FUEL);
	return (true);
}

void		use_asset(t_env *d, t_objects *asset)
{
	d->player.health += asset->stat_mod.heal;
	d->player.health = MIN(100, d->player.health);
	d->player.health -= asset->stat_mod.damage;
	d->weapon_type.current_ammo += asset->stat_mod.ballista_ammo;
	d->weapon_type.current_ammo = MIN(d->weapon_type.current_ammo, MAX_BULLETS);
	if (asset->stat_mod.heal > 0)
	{
		play_sound(d, HEALTH_SOUND, v3_to_v2(d->cam.pos));
		buf_to_collor2(d, asset->stat_mod.heal / 2, HEALTH_COLO);
	}
	if (!check_jetpack(d, asset))
		return (massege_print(d, "INVENTORY IS FULL"));
	asset->used = true;
}

void		assets_to_interactive(t_env *d)
{
	int			i;
	t_vec2f		dist;
	double		dist_len;
	t_objects	*asset;

	i = -1;
	while (d->objects_n && ++i < d->objects[d->this_sect][0].objects_n)
	{
		asset = &d->objects[d->this_sect][i];
		if (asset->used || asset->is_on_ceil)
			return ;
		dist = v2_min(v3_to_v2(d->cam.pos), asset->world_pos);
		dist_len = v2_len(dist);
		if (dist_len > COLLISION_R)
			return ;
		if (asset->collision)
		{
			d->cam.pos.x = asset->world_pos.x + dist.x * COLLISION_R / dist_len;
			d->cam.pos.z = asset->world_pos.y + dist.y * COLLISION_R / dist_len;
		}
		if (asset->is_autopick && !check_if_return(d, asset))
			use_asset(d, asset);
	}
}
