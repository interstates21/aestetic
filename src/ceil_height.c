/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 22:54:22 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

double	get_ceilheight_player(t_data *d, int16_t sectnum)
{
	double		ceil_height;
	t_vec2f		v;
	t_sector	*s;

	v.x = d->cam.pos.x;
	v.y = d->cam.pos.z;
	s = &d->sectors[sectnum];
	ceil_height = get_ceil_height(s, d->walls, sectnum, v);
	return (ceil_height);
}

double	get_ceildh(t_data *d, t_sector *sect, t_vec2f v)
{
	double		ceil_height;
	int16_t		n;
	t_sector	*s;
	double		res;

	if (!sect)
		print_err("get ceil sector is null");
	n = sect - d->sectors;
	s = &d->sectors[n];

	ceil_height = get_ceil_height(s, d->walls, n, v);
	res = ceil_height - d->cam.pos.y;
	return (res);
}

double	get_ceil_height(t_sector *sect, t_wall *walls, int16_t sectnum,
																	t_vec2f p)
{
	t_vec2f		center;
	double		angle;

	if (sectnum >= 0)
	{
		if (!(sect->slopeceil))
			return (sect->ceilheight);
		get_sector_center(&center, walls, sect->numwalls, sect->firstwallnum);
		angle = get_angle(sect->slopeceil_orientation,
												sect->is_animatedslopeceil);
		p = v2_min(p, center);
		v2_rot(&p, angle);
		p = v2_plus(p, center);
		return (tan_calculations(sect->ceilheight, sect->slopeceil, p, center));
	}
	print_err("0 sectors");
	return (1);
}
