/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:33:10 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 23:33:19 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec3f	v3_scale(t_vec3f a, double n)
{
	t_vec3f c;

	c.x = a.x * n;
	c.y = a.y * n;
	c.z = a.z * n;
	return (c);
}

t_vec2f	v2_scale(t_vec2f a, double n)
{
	t_vec2f c;

	c.x = a.x * n;
	c.y = a.y * n;
	return (c);
}
