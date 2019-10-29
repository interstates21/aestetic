/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_constructors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:39:20 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 16:11:58 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_v2_pair	new_v2_pair(t_vec2f v1, t_vec2f v2)
{
	t_v2_pair pair;

	pair.v1 = v1;
	pair.v2 = v2;
	return (pair);
}

t_vec2f		new_v2(double x, double y)
{
	t_vec2f v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec3f		new_v3(double x, double y, double z)
{
	t_vec3f v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
