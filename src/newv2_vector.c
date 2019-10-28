/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newv2_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:38:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 23:42:32 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	new_v2zero()
{
	t_vec2f v;

	v.x = 0.0;
	v.y = 0.0;
	return (v);
}

t_vec2	new_v2int(int x, int y)
{
	t_vec2 v;

	v.x = 0;
	v.y = 0;
	return (v);
}

t_vec2	add_v2int(t_vec2 a, t_vec2 b)
{
	t_vec2 v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	return (v);
}

t_vec2	min_v2int(t_vec2 a, t_vec2 b)
{
	t_vec2 v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	return (v);
}

t_vec2	mult_v2int(t_vec2 a, t_vec2 b)
{
	t_vec2 v;

	v.x = a.x * b.x;
	v.y = a.y * b.y;
	return (v);
}
