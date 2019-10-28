/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rot_monster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:48:59 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 18:30:39 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static uint8_t	get_option(double r)
{
	if (r > M_PI)
	{
		if (r < 1.25 * M_PI)
			return (1);
		if (r < 1.5 * M_PI)
			return (0);
		if (r < 1.75 * M_PI)
			return (7);
		if (r < DOUBLE_PI)
			return (6);
	}
	if (r > 0.75 * M_PI)
		return (2);
	if (r > M_PI_2)
		return (3);
	if (r > M_PI_4)
		return (4);
	if (r < 0)
		return (6);
	return (5);
}

uint8_t			get_nb_anim_from_rotation(double m_rotation,
		t_vec2f mon_pos, t_vec2f p_pos)
{
	double	r;
	t_vec2f	vs;
	double	vr;

	vs = v2_min(mon_pos, p_pos);
	vr = atan2(vs.y, vs.x);
	r = (vr - m_rotation) + M_PI_2;
	if (r > DOUBLE_PI)
		r -= DOUBLE_PI;
	if (r < 0)
		r += DOUBLE_PI;
	r = r - 0.125 * M_PI;
	return (get_option(r));
}
