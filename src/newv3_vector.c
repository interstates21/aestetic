/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newv3_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:35:55 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 15:55:19 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double	vec3f_length(t_vec3f v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3f	new_v3_proj(double x, double y)
{
	t_vec3f v;

	v.x = x;
	v.y = y;
	v.z = 0;
	return (v);
}

t_vec3f	new_v3zero(void)
{
	t_vec3f v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	return (v);
}

t_vec3f	new_v3z(double z)
{
	t_vec3f v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = z;
	return (v);
}
