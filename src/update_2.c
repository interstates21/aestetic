/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 05:25:27 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:50:11 by bdeomin          ###   ########.fr       */
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
			demeanor_monst(d, &monsters[i], i);
		monst_st_animate(&monsters[i], d->monster_type, d);
	}
}

void	new_proj_2(t_env *d, short i, bool coll)
{
	int16_t	update_sect;

	update_sect = 0;
	if (!coll && (update_sect = new_proj_curs((int16_t[2]){
					d->anim_rots[i].this_sect, -1}, d, NB_OF_SECTOR_DEPTH,
					d->anim_rots[i].pos)) >= 0)
	{
		if (update_sect != d->anim_rots[i].this_sect)
		{
			list_swp(IS_PROJECTILE, i, d,
					(int[2]){d->anim_rots[i].this_sect, update_sect});
		}
		d->anim_rots[i].this_sect = update_sect;
		new_proj_animate(&d->anim_rots[i], d, i, coll);
	}
	else if (update_sect == -2)
	{
		d->anim_rots[i].is_active = false;
		mailing_deleted(i, &d->sectors[d->anim_rots[i].this_sect],
				IS_PROJECTILE);
	}
	else
		new_proj_animate(&d->anim_rots[i], d, i, true);
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
				new_proj_animate(&d->anim_rots[i], d, i, false);
				i++;
				continue ;
			}
			if (d->anim_rot_type[d->anim_rots[i].id_type].threat_to_monster)
				coll = proj_monst_colided(d, &d->sectors[d->anim_rots[i].
						this_sect], &d->anim_rots[i]);
			if (d->anim_rot_type[d->anim_rots[i].id_type].threat_to_player)
				coll = proj_play_colided(d, &d->anim_rots[i]);
			new_proj_2(d, i, coll);
		}
}

void	reloade_2(t_env *d)
{
	d->player_floor_h = height_play_fl_val(d, d->this_sect);
	d->player_ceil_h = height_play_cl_val(d, d->this_sect);
	jumping(d);
	actio_pl(d);
	update_monsters(&d->monst_n, d->monsters, d);
	new_proj(d);
	d->sparks = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	view_danget_stash(d);
}
