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

void	update_monsters(uint16_t *nummonsters,
		t_monster monsters[MAXNUMMONSTERS], t_data *d)
{
	short	i;

	i = -1;
	(void)d;
	(void)monsters;
	while (++i < *nummonsters)
	{
		if (monsters[i].can_collide)
			monster_behaviour(d, &monsters[i], i);
		monster_anim_state(&monsters[i], d->monster_type, d);
	}
}

void	new_proj_2(t_data *d, short i, bool coll)
{
	int16_t	update_sect;

	update_sect = 0;
	if (!coll && (update_sect = update_cursect_proj((int16_t[2]){
					d->projectiles[i].cursectnum, -1}, d, NB_OF_SECTOR_DEPTH,
					d->projectiles[i].pos)) >= 0)
	{
		if (update_sect != d->projectiles[i].cursectnum)
		{
			swap_list(IS_PROJECTILE, i, d,
					(int[2]){d->projectiles[i].cursectnum, update_sect});
		}
		d->projectiles[i].cursectnum = update_sect;
		update_anim_projectile(&d->projectiles[i], d, i, coll);
	}
	else if (update_sect == -2)
	{
		d->projectiles[i].is_active = false;
		destroy_mail(i, &d->sectors[d->projectiles[i].cursectnum],
				IS_PROJECTILE);
	}
	else
		update_anim_projectile(&d->projectiles[i], d, i, true);
}

void	new_proj(t_data *d)
{
	short	i;
	bool	coll;

	i = -1;
	coll = false;
	while (++i < MAX_PROJECTILES)
		if (d->projectiles[i].is_active)
		{
			if (d->projectiles[i].has_collided)
			{
				update_anim_projectile(&d->projectiles[i], d, i, false);
				i++;
				continue ;
			}
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_monster)
				coll = collision_proj_monster(d, &d->sectors[d->projectiles[i].
						cursectnum], &d->projectiles[i]);
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_player)
				coll = collision_proj_player(d, &d->projectiles[i]);
			new_proj_2(d, i, coll);
		}
}

void	update_2(t_data *d)
{
	d->floorheightplayer = get_floorheight_player(d, d->cursectnum);
	d->ceilheightplayer = get_ceilheight_player(d, d->cursectnum);
	jump(d);
	player_actions(d);
	update_monsters(&d->nummonsters, d->monsters, d);
	new_proj(d);
	d->lightblink = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	check_dangerous_area(d);
}
