/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_anim_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/27 02:38:25 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	precompute_texanim(t_data *d)
{
	int			i;
	SDL_Surface	*s;
	int			framenum;
	int			numframes;

	framenum = SDL_GetTicks() / 80;
	i = -1;
	while (++i < d->nb_textures)
	{
		s = d->textures[i];
		if ((numframes = (s->h / s->w)) > 5)
			s->userdata = (void*)(intptr_t)(framenum % numframes + 1);
		else
			s->userdata = 0;
	}
}

void	monst(t_monster *monster, t_monster_type *monster_type, t_data *d, int num)
{
	if (num == 1)
	{
		monster->anim_time--;
		if (monster->anim_time)
			return ;
		monster->anim_state = monster_type[monster->
		id_type].anim_order[monster->anim_state];
		monster->anim_time = SPEED_ANIM;
		if (monster->anim_state == MOTHER_DEMON_ATTACK &&
			monster->anim_time == SPEED_ANIM)
		{
			create_projectile_monster(d, FIREBALL_1, monster);
			play_sound(d, MOTHER_ATK_SOUND, monster->pos);
		}
	}
	else if (num == 2)
		monster->anim_time--;
		if (monster->anim_time)
			return ;
		monster->anim_state = monster_type[monster->
			id_type].anim_order[monster->anim_state];
		if (monster->anim_state < 4)
			monster->anim_time = SPEED_ANIM_CHARG;
		else
			monster->anim_time = SPEED_ANIM_CHOW;
}

void	monster_anim_state(t_monster *monster,
		t_monster_type *monster_type, t_data *d)
{
	if (monster->id_type == MOTHERDEMON)
		monst(monster, monster_type, d, 1);
	if (monster->id_type == CHARGINGDEMON)
		monst(monster, monster_type, d, 1);
}
