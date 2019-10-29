/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_asseting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:26:21 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 21:51:05 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

/*
** bdeomin
*/

void	assets_to_draw(t_env *d, t_projdata *p, int16_t sectnum, int i)
{
	t_objects	*asset;
	t_vec3f		vect;

	asset = &d->objects[sectnum][i];
	if (!asset->used)
	{
		vect = v2_to_v3(asset->world_pos);
		vect.y = (asset->is_on_floor) ?
			get_floordh(d, p->sector, v3_to_v2(vect)) :
			get_ceildh(d, p->sector, v3_to_v2(vect));
		p->is_on_floor = asset->is_on_floor;
		proj_to_asset(d, p, vect, d->assets_texture[asset->picnum]);
		liting_assets(d, p, d->assets_texture[asset->picnum]);
	}
}

void	d_asseting(t_env *d, t_projdata *p, int16_t sectnum)
{
	int			i;

	sectnum = p->sector - d->sectors;
	i = -1;
	while (d->objects_n && ++i < d->objects[sectnum][0].objects_n)
		assets_to_draw(d, p, sectnum, i);
}
