/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monters_inicialization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/28 00:37:25 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	add_monster(t_sector *sector, int16_t id_of_monster)
{
	t_sprite_list	*new;
	t_sprite_list	*buff;

	new = pure_malloc(sizeof(*new), "ERROR");
	new->next = NULL;
	new->id = id_of_monster;
	new->type = IS_MONSTER;
	if (!(buff = sector->sprite_list))
	{
		sector->sprite_list = new;
		return ;
	}
	while (buff->next)
	{
		buff = buff->next;
	}
	buff->next = new;
}

void	initialize_all_monster(t_env *d,
		t_monster *monster, int16_t id_of_monster)
{
	monster->life = d->monster_type[monster->id_type].health * d->hard;
	monster->activated = false;
	monster->anim_state = 0;
	monster->rot = 1.5 * M_PI;
	monster->anim_time = 25;
	monster->can_collide = true;
	monster->timer = 0;
	add_monster(&d->sectors[monster->this_sect], id_of_monster);
}

void	init_monster_type_2(t_env *d)
{
	int i;

	i = 0;
	while (i < 18)
	{
		(i == 3) ? d->monster_type[CHARGINGDEMON].anim_order[i++] = 0 : 0;
		(i == 6) ? d->monster_type[CHARGINGDEMON].anim_order[6] = 4 : 0;
		(i == 6) ? i = 13 : 0;
		d->monster_type[CHARGINGDEMON].anim_order[i] = (i + 1);
		i++;
	}
	d->monster_type[CHARGINGDEMON].anim_order[18] = 18;
}

void	init_monst(t_env *d)
{
	d->monster_type[CHARGINGDEMON].height = 1.5;
	d->monster_type[CHARGINGDEMON].floating = 0.1;
	d->monster_type[CHARGINGDEMON].size = 6.0;
	d->monster_type[CHARGINGDEMON].health = 110;
	d->monster_type[CHARGINGDEMON].hitbox_radius = 0.6;
	d->monster_type[MOTHERDEMON].height = 2.0;
	d->monster_type[MOTHERDEMON].floating = 0.1;
	d->monster_type[MOTHERDEMON].size = 7.0;
	d->monster_type[MOTHERDEMON].health = 80;
	d->monster_type[MOTHERDEMON].hitbox_radius = 0.7;
	d->monster_type[MOTHERDEMON].id_of_proj = FIREBALL_1;
}

void	init_monster_type(t_env *d)
{
	short	i;

	i = 0;
	while (i < 18)
	{
		(i == 3) ? d->monster_type[MOTHERDEMON].anim_order[i++] = 0 : 0;
		(i == 6) ? d->monster_type[MOTHERDEMON].anim_order[6] = 0 : 0;
		(i == 6) ? i = 10 : 0;
		d->monster_type[MOTHERDEMON].anim_order[i] = i + 1;
		i++;
	}
	d->monster_type[MOTHERDEMON].anim_order[18] = 18;
}

void	monters_inicialization(t_env *d)
{
	short	i;

	init_monster_type(d);
	init_monster_type_2(d);
	init_monst(d);
	i = 0;
	while (i < d->monst_n)
	{
		initialize_all_monster(d, &(d->monsters[i]), i);
		i++;
	}
}
