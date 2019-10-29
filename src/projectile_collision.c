/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:16:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:23:38 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	monster_hit_2(t_env *d, uint16_t damage, uint16_t id_monster)
{
	if ((d->monsters[id_monster].life -= damage) <= 0)
	{
		d->monsters[id_monster].can_collide = false;
		d->monsters[id_monster].activated = false;
		d->monsters[id_monster].anim_state = d->monsters[id_monster].id_type ==
			MOTHERDEMON ? 10 : 13;
		d->monsters[id_monster].anim_time = 20;
		play_sound(d, d->monsters[id_monster].id_type == MOTHERDEMON ?
				MOTHER_DEATH_SOUND : CHARG_DEATH_SOUND, d->monsters[id_monster].
				pos);
	}
}

void		monster_hit(t_env *d, uint16_t damage, uint16_t id_monster)
{
	t_sprite_list	*tmp;

	if (!d->monsters[id_monster].activated)
	{
		d->monsters[id_monster].activated = true;
		d->monsters[id_monster].timer = 2;
		play_sound(d, d->monsters[id_monster].id_type == MOTHERDEMON ?
				MOTHER_AGRO_SOUND : CHARG_AGRO_SOUND, d->monsters[id_monster].
				pos);
		tmp = d->sectors[d->monsters[id_monster].this_sect].sprite_list;
		while (tmp)
		{
			if (tmp->type == IS_MONSTER && d->monsters[tmp->id].activated ==
					false)
				activate_tring(d, &d->monsters[tmp->id],
						d->monsters[id_monster].pos, false);
			tmp = tmp->next;
		}
	}
	monster_hit_2(d, damage, id_monster);
}

bool		collision_proj_one_monst(t_env *d, t_monster *monster,
		t_anim_rot *projectile, t_vec3f newpos)
{
	double		dist;
	t_vec2f		vec2f_tmp[2];
	double		floor_height;

	floor_height = height_fl_val(&d->sectors[monster->this_sect],
								d->walls, monster->this_sect, monster->pos);
	dist = v2_len(v2_min(v3_to_v2(newpos), monster->pos));
	if (dist < d->anim_rot_type[projectile->id_type].hitbox_radius +
			d->monster_type[monster->id_type].hitbox_radius)
		if (newpos.y > floor_height
		&& newpos.y < d->monster_type[monster->id_type].height)
		{
			vec2f_tmp[0] = v2_min(new_v2(projectile->pos.x,
											projectile->pos.z), monster->pos);
			vec2f_tmp[1] =
			new_v2(d->monster_type[monster->id_type].hitbox_radius +
			d->anim_rot_type[projectile->id_type].hitbox_radius, 0.0);
			actualize_dir(atan2(vec2f_tmp[0].y, vec2f_tmp[0].x), &vec2f_tmp[1]);
			projectile->pos.x = monster->pos.x + vec2f_tmp[1].x;
			projectile->pos.z = monster->pos.y + vec2f_tmp[1].y;
			projectile->pos.y = (newpos.y + projectile->pos.y) * 0.5;
			return (true);
		}
	return (false);
}

bool		proj_monst_colided(t_env *d, t_sec *sector,
		t_anim_rot *projectile)
{
	t_vec3f			newpos;
	t_sprite_list	*tmp;

	newpos = v3_plus(projectile->pos, projectile->dir);
	tmp = sector->sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
			if (collision_proj_one_monst(d, &d->monsters[tmp->id], projectile,
						newpos))
			{
				monster_hit(d, d->anim_rot_type[projectile->id_type].damage,
						tmp->id);
				projectile->target = &d->monsters[tmp->id];
				projectile->dir = v3_min(newpos,
						v2_to_v3(d->monsters[tmp->id].pos));
				return (true);
			}
		tmp = tmp->next;
	}
	projectile->pos = newpos;
	return (false);
}

bool		proj_play_colided(t_env *d, t_anim_rot *projectile)
{
	t_vec3f	newpos;
	t_vec3f	tmp_pos;
	t_vec2f	tmp;
	double	dist;

	newpos = v3_plus(projectile->pos, projectile->dir);
	dist = vec3f_length(v3_min(newpos, d->cam.pos));
	if (dist < d->anim_rot_type[projectile->
			id_type].hitbox_radius + PLAYER_HITBOX)
	{
		tmp_pos = v3_min(projectile->pos, d->cam.pos);
		tmp = new_v2(MIN_DIST_TO_PLAYER, 0.0);
		proj_to_hit_play(d, projectile);
		actualize_dir(atan2(tmp_pos.y, tmp_pos.x) - M_PI_2, &tmp);
		projectile->pos = new_v3(
			tmp.x + d->cam.pos.x,
				d->cam.pos.y,
				tmp.y + d->cam.pos.z);
		projectile->pos = newpos;
		return (true);
	}
	projectile->pos = newpos;
	return (false);
}
