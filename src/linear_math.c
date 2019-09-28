/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:26:16 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/28 16:26:17 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"

double		xprod(t_v2f a, t_v2f b)
{
	return ((double)(a.x * b.y - b.x * a.y));
}

double		line_eq(double k, double x, double b)
{
	return (k * x + b);
}

void		rotate_z(t_vt *p, float teta)
{
	float tmp;
	float cos_teta;
	float sin_teta;

	teta *= M_PI / 180.0;
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	tmp = p->x;
	p->x = p->x * cos_teta - p->y * sin_teta;
	p->y = tmp * sin_teta + p->y * cos_teta;
}
