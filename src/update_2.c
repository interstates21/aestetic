/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 05:25:27 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 22:26:42 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

//not refact

void	update_monsters(uint16_t *monst_n,
		t_monster monsters[MAXNUMMONSTERS], t_env *d)
{
	short	i;

	i = -1;
	(void)d;
	(void)monsters;
	while (++i < *monst_n)
	{
		if (monsters[i].can_collide)
			monster_behaviour(d, &monsters[i], i);
		monster_anim_state(&monsters[i], d->monster_type, d);
	}
}

void	new_proj_2(t_env *d, short i, bool coll)
{
	int16_t	update_sect;

	update_sect = 0;
	if (!coll && (update_sect = update_cursect_proj((int16_t[2]){
					d->anim_rots[i].this_sect, -1}, d, NB_OF_SECTOR_DEPTH,
					d->anim_rots[i].pos)) >= 0)
	{
		if (update_sect != d->anim_rots[i].this_sect)
		{
			swap_list(IS_PROJECTILE, i, d,
					(int[2]){d->anim_rots[i].this_sect, update_sect});
		}
		d->anim_rots[i].this_sect = update_sect;
		update_anim_projectile(&d->anim_rots[i], d, i, coll);
	}
	else if (update_sect == -2)
	{
		d->anim_rots[i].is_active = false;
		destroy_mail(i, &d->sectors[d->anim_rots[i].this_sect],
				IS_PROJECTILE);
	}
	else
		update_anim_projectile(&d->anim_rots[i], d, i, true);
}

void	new_proj(t_env *d)
{
	short	i;
	bool	coll;

	i = -1;
	coll = false;
	while (++i < N_ANIM_ROTS)
		if (d->anim_rots[i].is_active)
		{
			if (d->anim_rots[i].has_collided)
			{
				update_anim_projectile(&d->anim_rots[i], d, i, false);
				i++;
				continue ;
			}
			if (d->anim_rot_type[d->anim_rots[i].id_type].threat_to_monster)
				coll = collision_proj_monster(d, &d->sectors[d->anim_rots[i].
						this_sect], &d->anim_rots[i]);
			if (d->anim_rot_type[d->anim_rots[i].id_type].threat_to_player)
				coll = collision_proj_player(d, &d->anim_rots[i]);
			new_proj_2(d, i, coll);
		}
}

void	update_2(t_env *d)
{
	d->player_floor_h = get_floorheight_player(d, d->this_sect);
	d->player_ceil_h = get_ceilheight_player(d, d->this_sect);
	jump(d);
	player_actions(d);
	update_monsters(&d->monst_n, d->monsters, d);
	new_proj(d);
	d->lightblink = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	check_dangerous_area(d);
}
