/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_down_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:59:42 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 15:53:01 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_vec2	move_down_vector2(t_vec2 v)
{
	v.y += 10;
	return (v);
}

t_vec3f	move_down_vector3(t_vec3f v)
{
	v.y += 10;
	return (v);
}
