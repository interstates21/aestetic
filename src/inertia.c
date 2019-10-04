/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:01:28 by nallani           #+#    #+#             */
/*   Updated: 2019/06/25 23:39:08 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

#define MAX_INERTIA 0.19

void	inertia(t_data *d, t_vec2f mvt)
{
	double	angle;

	d->inertia.x += mvt.x;
	d->inertia.y += mvt.y;
	if (vec2f_length(d->inertia) > MAX_INERTIA)
	{
		angle = atan2(d->inertia.y, d->inertia.x) - M_PI_2;
		d->inertia = (t_vec2f){ 0.0, MAX_INERTIA };
		actualize_dir(angle, &d->inertia);
	}
	d->inertia = vec2f_length(d->inertia) > 0.001
	? mul_vec2f(d->inertia, 0.9) : (t_vec2f){ 0, 0 };
}

void	change_inertia(t_data *d, double angle, double length)
{
	d->inertia = (t_vec2f){ length, 0.0 };
	actualize_dir(angle, &d->inertia);
}
