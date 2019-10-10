#include "../includes/doom_nukem.h"
/*
bool	pickup_asset(t_data *d)
{
	int			i;
	t_assets	*asset;

	i = -1;
	while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
	{
		asset = &d->assets[d->cursectnum][i];
		if (v2_len(v2_min(v3_to_v2(d->cam.pos), asset->world_pos)) <
				1.5 && !asset->used &&
				(asset->is_interactive || asset->is_autopick ||
				asset->is_key || asset->is_jetpack))
		{
			use_asset(d, asset);
			return (true);
		}
	}
	return (false);
}

void	press_e(t_data *d)
{
	if (pickup_asset(d))
		return ;
	else if (activate_door(d, &d->sectors[d->cursectnum]))
		return ;
}
*/