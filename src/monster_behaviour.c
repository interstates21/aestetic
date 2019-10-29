/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_behaviour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:39:48 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 17:41:33 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	motherdemon_behaviour_change_after_attack(t_env *d,
		t_monster *monster, double rand, t_vec2f tmp)
{
	t_vec2f	tmp2;

	if (v2_len(v2_min(v3_to_v2(d->cam.pos), monster->pos))
			< LONG_RANGE)
	{
		rand = ((abs((int)(monster->pos.x * 1000)) % 63) + 1);
		if (!(SDL_GetTicks()))
			return (false);
		rand = rand - (int)(rand / (2 * M_PI)) * 2 * M_PI;
		actualize_dir(rand, &tmp);
		month_ini(rand, tmp, tmp2, monster);
	}
	else
	{
		tmp2 = v2_min(monster->pos, v3_to_v2(d->cam.pos));
		rand = atan2(tmp2.y, tmp2.x) + M_PI;
		actualize_dir(rand, &tmp);
		tmp = v2_scale(tmp, 1.5);
		month_ini(rand, tmp, tmp2, monster);
	}
	return (true);
}

void	motherdemon_behaviour_change_pattern(t_env *d, t_monster *monster)
{
	t_vec2f tmp;
	double	rand;
	bool	ret;

	tmp.x = 0.03;
	tmp.y = 0.0;
	rand = 0;
	ret = false;
	if (monster->anim_state == 6)
		ret = motherdemon_behaviour_change_after_attack(d, monster, rand, tmp);
	if (!ret)
	{
		tmp = v2_min(v3_to_v2(d->cam.pos), monster->pos);
		monster->anim_state = 4;
		monster->anim_time = 10;
		monster->rot = atan2(tmp.y, tmp.x);
		monster->timer = 29;
	}
}

void	motherdemon_behaviour(t_env *d, t_monster *monster, uint16_t id)
{
	short	new_sect;
	int		protection;

	if ((monster->timer > 0) && (monster->anim_state < 4) && !(protection = 0))
	{
		monster->pos = v2_plus(monster->pos, monster->dir);
		monst_by_monst_colided(d, monster->this_sect, monster);
		while (collision_monster(d, &d->sectors[monster->this_sect],
					&monster->pos, COLLISION_DIST_MOTHERDEMON))
			if (++protection > 6)
				break ;
		if (monster->timer > 2)
			monster->timer -= 2;
		new_sect = new_smart_curs(d, 2, monster->pos,
				monster->this_sect);
		if (new_sect != monster->this_sect && new_sect != -1)
		{
			list_swp(IS_MONSTER, id, d, (int[2]){monster->this_sect,
					new_sect});
			monster->this_sect = new_sect;
		}
	}
	if (!monster->timer)
		motherdemon_behaviour_change_pattern(d, monster);
}

void	activate_tring(t_env *d, t_monster *monster, t_vec2f pos, bool recur)
{
	t_sprite_list	*tmp;

	if (v2_len(v2_min(monster->pos, pos)) <
			ACTIVATION_RADIUS)
	{
		monster->activated = true;
		monster->timer = 2;
		play_sound(d, monster->id_type == MOTHERDEMON ? MOTHER_AGRO_SOUND :
				CHARG_AGRO_SOUND, monster->pos);
	}
	if (!recur || monster->activated == false)
		return ;
	tmp = d->sectors[monster->this_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].activated == false)
			activate_tring(d, &d->monsters[tmp->id], monster->pos, false);
		tmp = tmp->next;
	}
}

void	demeanor_monst(t_env *d, t_monster *monster, uint16_t id)
{
	if (!monster->can_collide)
		return ;
	if (!monster->activated)
		activate_tring(d, monster, v3_to_v2(d->cam.pos), true);
	if (!monster->activated)
		return ;
	monster->timer--;
	if (monster->id_type == MOTHERDEMON)
		motherdemon_behaviour(d, monster, id);
	if (monster->id_type == CHARGINGDEMON)
		demeanor_char_demyon(d, monster, id);
}
