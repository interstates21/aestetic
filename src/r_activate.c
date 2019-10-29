/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_activate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:08:45 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:03:36 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	is_usable(t_objects *objects)
{
	if (objects->is_interactive)
		return (true);
	if (objects->is_autopick)
		return (true);
	if (objects->is_jetpack)
		return (true);
	return (false);
}

bool	is_in_range(t_env *d, t_objects *objects)
{
	t_vec2f cam_proj;
	double	len;

	cam_proj = v3_to_v2(d->cam.pos);
	len = v2_len(v2_min(cam_proj, objects->world_pos));
	if (len < PICKUP_RANGE)
		return (true);
	return (false);
}

void	pickup_asset(t_env *d)
{
	int			i;
	t_objects	*objects;
	bool		picked;

	i = -1;
	picked = false;
	while (d->objects_n && ++i < d->objects[d->this_sect][0].objects_n)
	{
		objects = &d->objects[d->this_sect][i];
		if (is_in_range(d, objects) && !objects->used && is_usable(objects))
		{
			picked = true;
			break ;
			use_asset(d, objects);
		}
	}
	if (!picked)
		door_use(d, &d->sectors[d->this_sect]);
}
