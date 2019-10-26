/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rot_monster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:48:59 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/25 22:10:09 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

//not_glob_refact

uint8_t	get_nb_anim_from_rotation_2(double rotation)
{
	if (rotation > 0.75 * M_PI)
		return (2);
	if (rotation > M_PI_2)
		return (3);
	if (rotation > M_PI_4)
		return (4);
	if (rotation < 0)
		return (6);
	return (5);
}

uint8_t	get_nb_anim_from_rotation(double monster_rotation,
		t_vec2f monster_pos, t_vec2f player_pos)
{
	double	rotation;
	double	vision_rotation;
	t_vec2f	vision;

	vision = v2_min(monster_pos, player_pos);
	vision_rotation = atan2(vision.y, vision.x);
	rotation = vision_rotation - monster_rotation;
	rotation += M_PI_2;
	if (rotation > 2 * M_PI)
		rotation -= 2 * M_PI;
	if (rotation < 0)
		rotation += 2 * M_PI;
	rotation = rotation - 0.125 * M_PI;
	if (rotation > M_PI)
	{
		if (rotation < 1.25 * M_PI)
			return (1);
		if (rotation < 1.5 * M_PI)
			return (0);
		if (rotation < 1.75 * M_PI)
			return (7);
		if (rotation < 2 * M_PI)
			return (6);
	}
	return (get_nb_anim_from_rotation_2(rotation));
}
