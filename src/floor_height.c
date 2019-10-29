/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_height.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:00:42 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:59:23 by bdeomin          ###   ########.fr       */
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
	floor_height = height_fl_val(s, d->walls, sectnum, v);
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
	floor_height = height_fl_val(s, d->walls, n, v);
	res = floor_height - d->cam.pos.y;
	return (res);
}

double	height_fl_val(t_sector *sect, t_wall *walls, int16_t sectnum,
																t_vec2f p)
{
	t_vec2f		center;
	double		h;
	double		angle;

	if (sectnum >= 0)
	{
		h = height_calc_fl(sect);
		if (!(sect->slope))
			return (h - height_calc_fl_eps(h));
		mid_sect_val(&center, walls, sect->n_walls, sect->firstwallnum);
		angle = angles_val(sect->slope_orientation, sect->is_animatedslope);
		p = v2_min(p, center);
		rotation_vector(&p, angle);
		p = v2_plus(p, center);
		return (angle_caluk_tang(h, sect->slope, p, center));
	}
	print_err("0 sectors");
	return (1);
}
