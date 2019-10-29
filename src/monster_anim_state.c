/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_anim_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:39:34 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	texture_pre_anim(t_env *d)
{
	int			i;
	SDL_Surface	*s;
	int			framenum;
	int			numframes;

	framenum = SDL_GetTicks() / 80;
	i = -1;
	while (++i < d->n_texts)
	{
		s = d->texts[i];
		if ((numframes = (s->h / s->w)) > 5)
			s->userdata = (void*)(intptr_t)(framenum % numframes + 1);
		else
			s->userdata = 0;
	}
}

void	monst(t_monster *m, t_monster_type *monster_type, t_env *d, int num)
{
	if (num == 1)
	{
		m->anim_time--;
		if (m->anim_time)
			return ;
		m->anim_state = monster_type[m->id_type].anim_order[m->anim_state];
		m->anim_time = SPEED_ANIM;
		if (m->anim_state == MOTHER_DEMON_ATTACK && m->anim_time == SPEED_ANIM)
		{
			proj_monst_creat(d, FIREBALL_1, m);
			play_sound(d, MOTHER_ATK_SOUND, m->pos);
		}
	}
	else if (num == 2)
	{
		m->anim_time--;
		if (m->anim_time)
			return ;
		m->anim_state = monster_type[m->id_type].anim_order[m->anim_state];
		if (m->anim_state < 4)
			m->anim_time = SPEED_ANIM_CHARG;
		else
			m->anim_time = SPEED_ANIM_CHOW;
	}
}

void	monst_st_animate(t_monster *monster,
		t_monster_type *monster_type, t_env *d)
{
	if (monster->id_type == MOTHERDEMON)
		monst(monster, monster_type, d, 1);
	if (monster->id_type == CHARGINGDEMON)
		monst(monster, monster_type, d, 1);
}
