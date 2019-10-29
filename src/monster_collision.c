/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:11:53 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:24:54 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_vec3f	update_pos_vec3f(t_vec3f new_pos, t_vec2f point, double radius)
{
	t_vec2f		tmp[2];

	tmp[0] = new_v2(new_pos.x - point.x, new_pos.z - point.y);
	tmp[1] = new_v2(radius, 0.0);
	actualize_dir(atan2(tmp[0].y, tmp[0].x), &tmp[1]);
	return (new_v3(tmp[1].x + point.x, new_pos.y, tmp[1].y + point.y));
}

t_vec2f	update_pos_vec2f(t_vec2f pos, t_vec2f point)
{
	t_vec2f		tmp;

	tmp = v2_min(pos, point);
	tmp = new_v2(0.0, MINIMUM_SIZE_AROUND_MONSTERS);
	actualize_dir(atan2(tmp.y, tmp.x), &tmp);
	return (v2_plus(point, tmp));
}

void	monst_by_monst_colided(t_env *d, short cur_sect, t_monster *monster)
{
	t_sprite_list	*tmp;

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide &&
				&d->monsters[tmp->id] != monster)
			if (v2_len(v2_min(d->monsters[tmp->id].pos, monster->pos))
					< MINIMUM_SIZE_AROUND_MONSTERS)
				monster->pos = update_pos_vec2f(monster->pos,
						d->monsters[tmp->id].pos);
		tmp = tmp->next;
	}
}

void	play_by_monst_colided(t_env *d, short cur_sect)
{
	t_sprite_list	*tmp;
	double			floor_height;
	t_vec2f			pos;

	tmp = d->sectors[cur_sect].sprite_list;
	pos = d->monsters[tmp->id].pos;
	while (tmp)
	{
		floor_height = height_fl_val(&d->sectors[cur_sect],
													d->walls, cur_sect, pos);
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
			if (v2_len(v2_min(d->monsters[tmp->id].pos,
				new_v2(d->cam.pos.x, d->cam.pos.z))) <
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius
						+ MONSTER_MIN_DIST_HITBOX && d->cam.pos.y <
							floor_height +
						d->monster_type[d->monsters[tmp->id].id_type].height)
			{
				d->cam.pos = update_pos_vec3f(d->cam.pos, d->monsters
						[tmp->id].pos, d->monster_type[d->monsters[tmp->id].
						id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX);
				play_and_monst_acive(d, &(d->monsters[tmp->id]));
			}
		tmp = tmp->next;
	}
}
