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

bool	is_usable(t_assets *assets) {
	if (assets->is_interactive)
		return (true);
	if (assets->is_autopick)
		return (true);
	if (assets->is_jetpack)
		return (true);
	return (false);
}

bool	is_in_range(t_env *d, t_assets *assets) {
	t_vec2f cam_proj;
	double	len;

	cam_proj = v3_to_v2(d->cam.pos);
	len = v2_len(v2_min(cam_proj, assets->world_pos));
	if (len < PICKUP_RANGE )
		return (true);
	return (false);
}

void 	pickup_asset(t_env *d)
{
	int			i;
	t_assets	*assets;
	bool		picked;

	i = -1;
	picked = false;
	while (d->nb_assets && ++i < d->assets[d->this_sect][0].nb_assets)
	{
		assets = &d->assets[d->this_sect][i];
		if (is_in_range(d, assets) && !assets->used && is_usable(assets))
		{
			picked = true;
			break ;
			use_asset(d, assets);
		}
	}
	if (!picked)
		door_use(d, &d->sectors[d->this_sect]);
}
