/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_monster.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:59:00 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:10:38 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	behaviour_update_charge(t_env *d, t_monster *monster)
{
	t_vec2f	tmp;
	double	new_angle;

	tmp = v2_min(monster->pos, v3_to_v2(d->cam.pos));
	new_angle = atan2(tmp.y, tmp.x) + M_PI;
	monster->dir = v2_scale(monster->dir, 0.9);
	tmp.x = 0.015;
	tmp.y = 0.0;
	actualize_dir(new_angle, &tmp);
	monster->dir = v2_plus(monster->dir, tmp);
	monster->rot = atan2(monster->dir.y, monster->dir.x);
	monster->pos = v2_plus(monster->pos, monster->dir);
}

void		dellay_char_demyon(t_monster *monster)
{
	monster->dir = new_v2zero();
	monster->timer = 30;
	if (monster->anim_state < 4)
	{
		monster->anim_state = 4;
		monster->anim_time = 17;
	}
}

static void	update_cursect_chargingdemon(t_env *d, t_monster *monster,
		uint16_t id)
{
	int16_t		new_sect;

	new_sect = new_smart_curs(d, 2, monster->pos, monster->this_sect);
	if (new_sect != monster->this_sect && new_sect != -1)
	{
		list_swp(IS_MONSTER, id, d, (int[2]){monster->this_sect, new_sect});
		monster->this_sect = new_sect;
	}
}

static void	init_load_monst(t_env *d, t_monster *monster, t_vec2f tmp)
{
	tmp = v2_min(monster->pos, v3_to_v2(d->cam.pos));
	monster->rot = atan2(tmp.y, tmp.x) + M_PI;
	tmp.x = 0.02;
	tmp.y = 0.0;
	actualize_dir(monster->rot, &tmp);
	monster->dir = tmp;
	monster->timer = 0xFF;
	monster->anim_state = 0;
	monster->anim_time = 7;
}

void		demeanor_char_demyon(t_env *d, t_monster *monster,
		uint16_t id)
{
	t_vec2f		tmp;

	if (monster->timer == 0 && monster->dir.x == 0.0)
		init_load_monst(d, monster, tmp);
	if (monster->timer && monster->dir.x != 0)
		behaviour_update_charge(d, monster);
	monst_by_monst_colided(d, monster->this_sect, monster);
	while (collision_monster(d, &d->sectors[monster->this_sect],
				&monster->pos, COLLISION_RANGE_CHARGINGDEMON))
		if (monster->timer < 240)
			dellay_char_demyon(monster);
	update_cursect_chargingdemon(d, monster, id);
}
