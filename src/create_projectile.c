/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_projectile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:34:05 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:40:17 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	set_projectile_id(t_env *d, short i, short id_of_proj_type)
{
	d->anim_rots[i].is_active = true;
	d->anim_rots[i].id_type = id_of_proj_type;
	d->anim_rots[i].dir.z = d->cam.cos *
		d->anim_rot_type[id_of_proj_type].speed;
	d->anim_rots[i].dir.y = d->cam.y_offset *
		Y_OFFSET_TO_ROT * d->anim_rot_type[id_of_proj_type].speed;
	d->anim_rots[i].dir.x = d->cam.sin *
		d->anim_rot_type[id_of_proj_type].speed;
	d->anim_rots[i].is_curr_anim =
		d->anim_rot_type[id_of_proj_type].anim_order[0];
	d->anim_rots[i].pos = d->cam.pos;
	d->anim_rots[i].has_collided = false;
	d->anim_rots[i].this_sect = d->this_sect;
	d->anim_rots[i].time_remaining_anim = 5;
	d->anim_rots[i].is_curr_anim = 0;
	d->anim_rots[i].weapon_id = d->player.curr_weap;
	d->anim_rots[i].target = NULL;
}

void	to_proj_creat(t_env *d, short id_of_proj_type)
{
	t_sprite_list	*nw;
	short			i;

	i = 0;
	while (i < N_ANIM_ROTS && d->anim_rots[i].is_active)
		i++;
	if (i == N_ANIM_ROTS)
		return ;
	nw = pure_malloc(sizeof(*nw), "ERROR");
	nw->next = d->sectors[d->this_sect].sprite_list;
	nw->type = IS_PROJECTILE;
	nw->id = i;
	set_projectile_id(d, i, id_of_proj_type);
	d->sectors[d->this_sect].sprite_list = nw;
}

void	set_projectile_id_monster(t_env *d, short i,
		short id_of_proj_type, t_monster *monster)
{
	d->anim_rots[i].is_active = true;
	d->anim_rots[i].id_type = id_of_proj_type;
	d->anim_rots[i].pos = new_v3(
		monster->pos.x,
		d->sectors[monster->this_sect].floorheight + 0.8,
		monster->pos.y);
	d->anim_rots[i].dir.z = sin(monster->rot) *
		d->anim_rot_type[id_of_proj_type].speed;
	d->anim_rots[i].dir.y = (d->cam.pos.y -
			(d->sectors[monster->this_sect].floorheight + 0.8)) /
		vec3f_length(v3_min(d->anim_rots[i].pos, d->cam.pos)) *
		d->anim_rot_type[id_of_proj_type].speed;
	d->anim_rots[i].dir.x = cos(monster->rot) *
		d->anim_rot_type[id_of_proj_type].speed;
	d->anim_rots[i].is_curr_anim =
		d->anim_rot_type[id_of_proj_type].anim_order[0];
	d->anim_rots[i].has_collided = false;
	d->anim_rots[i].weapon_id = d->monster_type[monster->id_type].id_of_proj;
	d->anim_rots[i].this_sect = monster->this_sect;
	d->anim_rots[i].time_remaining_anim = 5;
	d->anim_rots[i].is_curr_anim = 0;
	d->anim_rots[i].target = NULL;
}

void	proj_monst_creat(t_env *d, short id_of_proj_type,
		t_monster *monster)
{
	t_sprite_list	*nw;
	short			i;

	i = 0;
	while (i < N_ANIM_ROTS && d->anim_rots[i].is_active)
		i++;
	if (i == N_ANIM_ROTS)
		return ;
	nw = pure_malloc(sizeof(*nw), "ERROR");
	nw->next = d->sectors[monster->this_sect].sprite_list;
	nw->type = IS_PROJECTILE;
	nw->id = i;
	set_projectile_id_monster(d, i, id_of_proj_type, monster);
	d->sectors[monster->this_sect].sprite_list = nw;
}
