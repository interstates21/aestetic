/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 04:20:43 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 04:56:49 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

double		shade_factor(t_data *d, t_sector *sector, double dist, int mode)
{
	double	factor;

	factor = (sector->blinking) ? d->lightblink : sector->light;
	if (dist && !sector->outdoor && sector->light == 1)
		mode == 0 ? (factor -= dist / 30) : (factor -= dist / 20);
	return (factor);
}

uint32_t	shade(double factor, uint32_t c)
{
	if (factor >= 1)
		return (c);
	if (factor <= 0)
		return (0);
	return (((int)(((c >> 16) & 0xff) * factor) << 16) |
			((int)(((c >> 8) & 0xff) * factor) << 8) |
			((int)(((c >> 0) & 0xff) * factor) << 0));
}
