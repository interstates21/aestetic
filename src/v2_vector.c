/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:36:55 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:55:09 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

float	v2_dot(t_vec2f v)
{
	return (v.x * v.x + v.y * v.y);
}

double	v2_len(t_vec2f v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	v2_atan(t_vec2f v1, t_vec2f v2)
{
	return (atan2(v1.x * v2.y - v1.y * v2.x, v1.x * v2.x + v1.y * v2.y));
}

void	rotation_vector(t_vec2f *p, double angle)
{
	t_vec2f temp;

	temp = *p;
	p->x = temp.x * cos(angle) - temp.y * sin(angle);
	p->y = temp.x * sin(angle) + temp.y * cos(angle);
}
