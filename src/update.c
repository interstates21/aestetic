/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 05:22:33 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 05:22:42 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	new_collided_proj(t_data *d, t_projectile *proj, bool anim,
		short id)
{
	int16_t		new_sectors;

	anim ? (proj->time_remaining_anim--) :
		((proj->current_anim_playing = d->projectile_type[proj->
			id_type].anim_order[proj->current_anim_playing]) &&
		(proj->time_remaining_anim = 2));
	if (proj->target)
	{
		proj->pos = v3_plus(v2_to_v3(proj->target->pos),
				proj->dir);
		if ((new_sectors = update_cursect_proj((int16_t[2]){proj->
						cursectnum, -1}, d, NB_OF_SECTOR_DEPTH,
						proj->pos)) != -1)
		{
			if (new_sectors != proj->cursectnum)
				swap_list(IS_PROJECTILE, id, d,
								(int[2]){proj->cursectnum, new_sectors});
			proj->cursectnum = new_sectors;
		}
	}
}

void	update_anim_projectile(t_projectile *proj, t_data *d, short id,
		bool collided)
{
	if (collided)
	{
		if (d->projectile_type[proj->id_type].threat_to_player)
			proj->dir = new_v3zero();
		proj->current_anim_playing =
			d->projectile_type[proj->id_type].anim_order[COLLISION_ID];
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
	if (d->projectile_type[proj->id_type].anim_order[
			proj->current_anim_playing] == MUST_BE_DESTROYED)
	{
		proj->is_active = false;
		destroy_mail(id, &d->sectors[proj->cursectnum], IS_PROJECTILE);
		return ;
	}
	new_collided_proj(d, proj, false, id);
}

void	update_doors(t_data *d)
{
	int i;

	i = -1;
	while (++i < MAXNUMWALLS)
		if (!d->walls[i].is_door || d->walls[i].neighborsect == -1)
			d->doorstate[i] = 1;
		else
		{
			d->doorstate[i] += d->dooranimstep[i];
			if (d->doorstate[i] >= 1 || d->doorstate[i] <= 0)
			{
				d->doorstate[i] = CLAMP(d->doorstate[i], 0, 1);
				d->dooranimstep[i] = 0;
			}
		}
}

void	update(t_data *d)
{
	int16_t	sect;

	if (d->player.health <= 0)
		handle_respawn(d);
	if (d->sectors[d->cursectnum].is_finish)
		handle_finish(d);
	update_doors(d);
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	movement(d);
	asset_collision(d);
	if ((sect = update_cursect_smart(d, DEPTH_TO_SCAN, v3_to_v2(d->cam.pos),
					d->cursectnum)) != -1)
	{
		if (sect != d->cursectnum && d->cam.pos.y < get_floorheight_player(d,
					sect) + d->player.minimum_height)
			d->player.minimum_height = d->cam.pos.y - get_floorheight_player(d,
					sect);
		d->cursectnum = sect;
	}
	update_2(d);
}
