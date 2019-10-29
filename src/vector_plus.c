/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:31:21 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 23:32:24 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	v2_plus(t_vec2f a, t_vec2f b)
{
	t_vec2f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_vec3f	v3_plus(t_vec3f a, t_vec3f b)
{
	t_vec3f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}
