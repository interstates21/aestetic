/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_math_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:10:26 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/03 17:10:28 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

void			black_magic(t_math *m, t_scene *s)
{
	m->y1 = (t_v2){HEIGHT / 2 - (int)(yaw(m->y_ceil, m->t1.y, s->player.yaw)
	* m->scale1.y), HEIGHT / 2 - (int)(yaw(m->y_floor, m->t1.y ,s->player.yaw)
	* m->scale1.y)};
	m->y2 = (t_v2){HEIGHT / 2 - (int)(yaw(m->y_ceil, m->t2.y, s->player.yaw)
	* m->scale2.y), HEIGHT / 2 - (int)(yaw(m->y_floor, m->t2.y, s->player.yaw)
	* m->scale2.y)};
	m->ny1 = (t_v2){HEIGHT / 2 - (int)(yaw(m->nyceil, m->t1.y, s->player.yaw)
	* m->scale1.y), HEIGHT / 2 - (int)(yaw(m->nyfloor, m->t1.y, s->player.yaw)
	* m->scale1.y)};
	m->ny2 = (t_v2){HEIGHT / 2 - (int)(yaw(m->nyceil, m->t2.y, s->player.yaw)
	* m->scale2.y), HEIGHT / 2 - (int)(yaw(m->nyfloor, m->t2.y, s->player.yaw)
	* m->scale2.y)};
}

int 		yaw(double y, double a, double w)
{
	return ((int)(y + a * w));
}
