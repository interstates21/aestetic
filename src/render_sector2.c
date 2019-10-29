/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:23:12 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 22:03:42 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_vec3f		transform_back(t_env *d, t_vec3f v)
{
	return (new_v3(v.x * d->cam.cos + v.z * d->cam.sin + d->cam.pos.x, v.y,
			v.x * -d->cam.sin + v.z * d->cam.cos + d->cam.pos.z));
}

void		transformvertex(t_env *d, t_vec2f v, double *x, double *z)
{
	v.x -= d->cam.pos.x;
	v.y -= d->cam.pos.z;
	*x = v.x * d->cam.cos - v.y * d->cam.sin;
	*z = v.x * d->cam.sin + v.y * d->cam.cos;
}

t_sec		*check_neighbor(t_env *d, int16_t nei)
{
	if (nei < 0 || nei >= d->n_sect)
		return (NULL);
	return (&d->sectors[nei]);
}
