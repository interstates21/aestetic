#include "../includes/doom_nukem.h"


static bool	check_if_return(t_data *d, t_assets *asset)
{
	if (d->player.health == 100 && asset->stat_mod.heal)
		return (true);
	if (d->weapon_type.current_ammo == d->weapon_type.max_ammo && asset->stat_mod.ballista_ammo)
		return (true);
	return (false);
}


static bool	check_jetpack(t_data *d, t_assets *asset)
{
	if (asset->stat_mod.ballista_ammo)
		play_sound(d, AMMO_SOUND, v3_to_v2(d->cam.pos));
	if (asset->is_key)
	{
		if (!d->slot1)
			d->slot1 = asset;
		else if (!d->slot2)
			d->slot2 = asset;
		else if (!d->slot3)
			d->slot3 = asset;
		else
			return (false);
	}
	if (asset->is_jetpack && (!d->slot1 || d->slot1->is_jetpack))
		d->slot1 = asset;
	else if (asset->is_jetpack && (!d->slot2 || d->slot2->is_jetpack))
		d->slot2 = asset;
	else if (asset->is_jetpack && (!d->slot3 || d->slot3->is_jetpack))
		d->slot3 = asset;
	else if (asset->is_jetpack)
		return (false);
	if (asset->is_jetpack)
		d->player.is_flying = MIN(d->player.is_flying + FUEL, MAX_FUEL);
	return (true);
}

void		use_asset(t_data *d, t_assets *asset)
{
	d->player.health += asset->stat_mod.heal;
	d->player.health = MIN(100, d->player.health);

	d->player.health -= asset->stat_mod.damage;
	d->weapon_type.current_ammo += asset->stat_mod.ballista_ammo;
	d->weapon_type.current_ammo = MIN(d->weapon_type.current_ammo, d->weapon_type.
			max_ammo);
	if (asset->stat_mod.heal > 0)
	{
		play_sound(d, HEALTH_SOUND, v3_to_v2(d->cam.pos));
		change_buf_colo(d, asset->stat_mod.heal / 2, HEALTH_COLO);
	}
	if (!check_jetpack(d, asset))
		return (invoke_msg(d, "INVENTORY IS FULL"));
	asset->used = true;
}

void		asset_collision(t_data *d)
{
	int i;
	t_vec2f	dist;
	double	dist_len;
	t_assets *asset;

	i = -1;
	while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
	{
		asset = &d->assets[d->cursectnum][i];
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
