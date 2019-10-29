/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:28:59 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 23:32:00 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	v2_min(t_vec2f a, t_vec2f b)
{
	t_vec2f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

t_vec3f	v3_min(t_vec3f a, t_vec3f b)
{
	t_vec3f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
