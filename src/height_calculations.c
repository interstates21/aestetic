/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:08:25 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:59:23 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

double	height_calc_fl(t_sec *s)
{
	double n;

	n = 0;
	if (s->is_elevator)
		n += sin(ANIMATION_TIME) * 0.5;
	n += s->floorheight;
	return (n);
}

void	mid_sect_val(t_vec2f *v, t_wall *walls, int n_walls,
														int current_wall)
{
	int			i;
	t_vec2f		p;
	double		interp;

	p = walls[current_wall + i].point;
	interp = 1.0 / n_walls;
	v->x = 0;
	v->y = 0;
	i = -1;
	while (++i < n_walls)
		*v = v2_plus(*v, p);
	*v = v2_scale(*v, interp);
}

double	angle_caluk_tang(double h, double slope, t_vec2f p, t_vec2f c)
{
	return (h + tan(slope * M_PI / 180) * (p.x - c.x));
}

double	angles_val(double o, bool is_animated)
{
	double temp;

	temp = o * M_PI / 180;
	if (is_animated)
		temp += ANIMATION_TIME;
	return (temp);
}

double	height_calc_fl_eps(double h)
{
	return (h > 5 ? 1.2 : 1.1);
}
