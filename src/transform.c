/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:45:09 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 16:11:50 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	translate(t_vec3f *p, t_vec3f move, int dir)
{
	p->x += (move.x * dir);
	p->y += (move.y * dir);
	p->z += (move.z * dir);
}

void	rot_x(t_vec3f *v, double ang, t_vec3f axis)
{
	double tmp;
	double cos_t;
	double sin_t;

	ang = ang * M_PI / 180.0;
	translate(v, axis, -1);
	sin_t = sin(ang);
	cos_t = cos(ang);
	tmp = v->y;
	v->y = v->y * cos_t - v->z * sin_t;
	v->z = tmp * sin_t + v->z * cos_t;
	translate(v, axis, 1);
}

void	rot_y(t_vec3f *v, double ang, t_vec3f axis)
{
	double tmp;
	double cos_t;
	double sin_t;

	ang = ang * M_PI / 180.0;
	translate(v, axis, -1);
	sin_t = sin(ang);
	cos_t = cos(ang);
	tmp = v->z;
	v->z = v->z * cos_t - v->x * sin_t;
	v->x = tmp * sin_t + v->x * cos_t;
	translate(v, axis, 1);
}

void	rot_z(t_vec3f *v, double ang, t_vec3f axis)
{
	double tmp;
	double cos_t;
	double sin_t;

	ang = ang * M_PI / 180.0;
	translate(v, axis, -1);
	sin_t = sin(ang);
	cos_t = cos(ang);
	tmp = v->x;
	v->x = v->x * cos_t - v->y * sin_t;
	v->y = tmp * sin_t + v->y * cos_t;
	translate(v, axis, 1);
}
