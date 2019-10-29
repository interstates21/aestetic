/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 05:22:33 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:51:14 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	new_collided_proj(t_env *d, t_anim_rot *proj, bool anim,
		short id)
{
	int16_t		new_sectors;

	anim ? (proj->time_remaining_anim--) :
		((proj->is_curr_anim = d->anim_rot_type[proj->
			id_type].anim_order[proj->is_curr_anim]) &&
		(proj->time_remaining_anim = 2));
	if (proj->target)
	{
		proj->pos = v3_plus(v2_to_v3(proj->target->pos),
				proj->dir);
		if ((new_sectors = new_proj_curs((int16_t[2]){proj->
						this_sect, -1}, d, NB_OF_SECTOR_DEPTH,
						proj->pos)) != -1)
		{
			if (new_sectors != proj->this_sect)
				list_swp(IS_PROJECTILE, id, d,
								(int[2]){proj->this_sect, new_sectors});
			proj->this_sect = new_sectors;
		}
	}
}

void	new_proj_animate(t_anim_rot *proj, t_env *d, short id,
		bool collided)
{
	if (collided)
	{
		if (d->anim_rot_type[proj->id_type].threat_to_player)
			proj->dir = new_v3zero();
		proj->is_curr_anim =
			d->anim_rot_type[proj->id_type].anim_order[COLLISION_ID];
		proj->time_remaining_anim = 5;
		proj->has_collided = true;
		play_sound(d, EXPLOSION_SOUND, v3_to_v2(proj->pos));
		return ;
	}
	if (proj->time_remaining_anim)
	{
		new_collided_proj(d, proj, true, id);
		return ;
	}
	if (d->anim_rot_type[proj->id_type].anim_order[
			proj->is_curr_anim] == MUST_BE_DESTROYED)
	{
		proj->is_active = false;
		mailing_deleted(id, &d->sectors[proj->this_sect], IS_PROJECTILE);
		return ;
	}
	new_collided_proj(d, proj, false, id);
}

void	update_doors(t_env *d)
{
	int i;

	i = -1;
	while (++i < N_WALLS)
		if (!d->walls[i].is_door || d->walls[i].neighborsect == -1)
			d->door_active[i] = 1;
		else
		{
			d->door_active[i] += d->anim_door[i];
			if (d->door_active[i] >= 1 || d->door_active[i] <= 0)
			{
				d->door_active[i] = CLAMP(d->door_active[i], 0, 1);
				d->anim_door[i] = 0;
			}
		}
}

void	reloade(t_env *d)
{
	int16_t	sect;

	if (d->player.health <= 0)
		respauning_h(d);
	if (d->sectors[d->this_sect].is_finish)
		ending_hd(d);
	update_doors(d);
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	to_move_func(d);
	assets_to_interactive(d);
	if ((sect = new_smart_curs(d, DEPTH_TO_SCAN, v3_to_v2(d->cam.pos),
					d->this_sect)) != -1)
	{
		if (sect != d->this_sect && d->cam.pos.y < height_play_fl_val(d,
					sect) + d->player.min_h)
			d->player.min_h = d->cam.pos.y - height_play_fl_val(d,
					sect);
		d->this_sect = sect;
	}
	reloade_2(d);
}
