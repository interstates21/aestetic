/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:11:45 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 22:57:01 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_sec		*check_neighbor(t_env *d, int16_t nei)
{
	if (nei < 0 || nei >= d->n_sect)
		return (NULL);
	return (&d->sectors[nei]);
}

t_vec3f		transform_back(t_env *d, t_vec3f v)
{
	return (new_v3(v.x * d->cam.cos + v.z * d->cam.sin + d->cam.pos.x, v.y,
			v.x * -d->cam.sin + v.z * d->cam.cos + d->cam.pos.z));
}
