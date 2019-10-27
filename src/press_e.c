/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:08:45 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 20:58:24 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

// not refact

bool	pickup_asset(t_data *d)
{
	int			i;
	t_assets	*assets;

	i = -1;
	while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
	{
		assets = &d->assets[d->cursectnum][i];
		if (v2_len(v2_min(v3_to_v2(d->cam.pos), assets->world_pos)) <
				1.5 && !assets->used &&
				(assets->is_interactive || assets->is_autopick ||
				assets->is_key || assets->is_jetpack))
		{
			use_asset(d, assets);
			return (true);
		}
	}
	return (false);
}

void	press_e(t_data *d)
{
	if (pickup_asset(d))
		return ;
	else if (door_use(d, &d->sectors[d->cursectnum]))
		return ;
}
