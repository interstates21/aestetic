/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:09:51 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 17:47:43 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		pixel_put(t_env *d, t_vec3f p, uint32_t color, int mode)
{
	int x;
	int	y;

	x = p.x;
	y = p.y;
	if (mode == 0)
	{
		if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
			((uint32_t*)d->sdl.screen->pixels)[x + y * WIDTH] = color;
	}
	else
	{
		x = x + y * WIDTH;
		if (x >= 0 && x < WIDTH * HEIGHT)
		{
			((uint32_t*)d->sdl.screen->pixels)[x] = color;
			d->z_buff[x] = p.z;
		}
	}
}

uint32_t	to_search_alpha(uint32_t old_colo, uint32_t new_colo)
{
	t_vec2f			percents;
	uint8_t			r[2];
	uint8_t			g[2];
	uint8_t			b[2];

	if (!(new_colo >> 24))
		return (old_colo);
	if (new_colo >> 24 == 0xFF)
		return (new_colo);
	percents.x = ((new_colo >> 24) & 0xFF) / 255.0;
	percents.y = 1 - percents.x;
	r[0] = (uint8_t)(0xFF & old_colo >> 16) * percents.y;
	g[0] = (uint8_t)(0xFF & old_colo >> 8) * percents.y;
	b[0] = (uint8_t)(0xFF & old_colo) * percents.y;
	r[1] = (uint8_t)(0xFF & new_colo >> 16) * percents.x;
	g[1] = (uint8_t)(0xFF & new_colo >> 8) * percents.x;
	b[1] = (uint8_t)(0xFF & new_colo) * percents.x;
	return (((r[0] + r[1]) << 16) + ((g[0] + g[1]) << 8) + (b[0] + b[1]));
}
