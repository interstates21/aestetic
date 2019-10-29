/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_height.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:00:42 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 20:09:49 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

double	get_floorheight_player(t_env *d, int16_t sectnum)
{
	double		floor_height;
	t_vec2f		v;
	t_sector	*s;

	s = &d->sectors[sectnum];
	v.x = d->cam.pos.x;
	v.y = d->cam.pos.z;
	floor_height = get_floor_height(s, d->walls, sectnum, v);
	return (floor_height);
}

double	get_floordh(t_env *d, t_sector *sect, t_vec2f v)
{
	double		floor_height;
	int16_t		n;
	t_sector	*s;
	double		res;

	if (!sect)
		print_err("get ceil sector is null");
	n = sect - d->sectors;
	s = &d->sectors[n];
	floor_height = get_floor_height(s, d->walls, n, v);
	res = floor_height - d->cam.pos.y;
	return (res);
}

double	get_floor_height(t_sector *sect, t_wall *walls, int16_t sectnum,
																t_vec2f p)
{
	t_vec2f		center;
	double		h;
	double		angle;

	if (sectnum >= 0)
	{
		h = calculate_max_floor_h(sect);
		if (!(sect->slope))
			return (h - calculate_floor_height_epsilon(h));
		get_sector_center(&center, walls, sect->numwalls, sect->firstwallnum);
		angle = get_angle(sect->slope_orientation, sect->is_animatedslope);
		p = v2_min(p, center);
		v2_rot(&p, angle);
		p = v2_plus(p, center);
		return (tan_calculations(h, sect->slope, p, center));
	}
	print_err("0 sectors");
	return (1);
}
