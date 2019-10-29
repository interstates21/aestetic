/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 21:09:40 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

double	height_play_cl_val(t_env *d, int16_t sectnum)
{
	double		ceil_height;
	t_vec2f		v;
	t_sec		*s;

	v.x = d->cam.pos.x;
	v.y = d->cam.pos.z;
	s = &d->sectors[sectnum];
	ceil_height = height_cl_val(s, d->walls, sectnum, v);
	return (ceil_height);
}

double	cl_calc_vec_cal(t_env *d, t_sec *sect, t_vec2f v)
{
	double		ceil_height;
	int16_t		n;
	t_sec		*s;
	double		res;

	if (!sect)
		print_err("get ceil sector is null");
	n = sect - d->sectors;
	s = &d->sectors[n];
	ceil_height = height_cl_val(s, d->walls, n, v);
	res = ceil_height - d->cam.pos.y;
	return (res);
}

double	height_cl_val(t_sec *sect, t_wall *walls, int16_t sectnum,
																	t_vec2f p)
{
	t_vec2f		center;
	double		angle;

	if (sectnum >= 0)
	{
		if (!(sect->slopeceil))
			return (sect->ceilheight);
		mid_sect_val(&center, walls, sect->n_walls, sect->firstwallnum);
		angle = angles_val(sect->slopeceil_orientation,
												sect->is_animatedslopeceil);
		p = v2_min(p, center);
		rotation_vector(&p, angle);
		p = v2_plus(p, center);
		return (angle_caluk_tang(sect->ceilheight, sect->slopeceil, p, center));
	}
	print_err("0 sectors");
	return (1);
}
