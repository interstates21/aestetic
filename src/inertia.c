/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:38:46 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	in_perk1(t_env *d, t_vec2f mvt, double perk1)
{
	if (v2_len(d->inertia) > MAX_INERTIA)
	{
		perk1 = atan2(d->inertia.y, d->inertia.x) - M_PI_2;
		d->inertia = new_v2(0.0, MAX_INERTIA);
		actualize_dir(perk1, &d->inertia);
	}
}

void	to_iner(t_env *d, t_vec2f mvt)
{
	double	perk1;

	d->inertia.x += mvt.x;
	d->inertia.y += mvt.y;
	in_perk1(d, mvt, perk1);
	if (v2_len(d->inertia) > 0.001)
		d->inertia = v2_scale(d->inertia, 0.9);
	else
	{
		d->inertia.x = 0;
		d->inertia.y = 0;
	}
}

void	to_ch_iter(t_env *d, double perk1, double length)
{
	d->inertia = new_v2(length, 0.0);
	actualize_dir(perk1, &d->inertia);
}
