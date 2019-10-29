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

static void	ups_m(t_env *env, t_monster mns[256], const uint16_t *m_n)
{
	short	k;

	k = 0;
	(void)env;
	(void)mns;
	while (k < *m_n)
	{
		if (mns[k].can_collide)
			demeanor_monst(env, &mns[k], k);
		monst_st_animate(&mns[k], env->monster_type, env);
		k++;
	}
}

static void	arbiter(t_env *env)
{
	short	k;

	k = -1;
	while (100 > ++k)
	{
		if (env->anim_rots[k].is_active)
			env->anim_rots[k].has_collided
			? fifth_sin(env, &k) : fourth_sin(env, k);
	}
}

void		reloade_2(t_env *env)
{
	env->player_floor_h = height_play_fl_val(env, env->this_sect);
	env->player_ceil_h = height_play_cl_val(env, env->this_sect);
	jumping(env);
	actio_pl(env);
	ups_m(env, env->monsters, &env->monst_n);
	arbiter(env);
	env->sparks = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	view_danget_stash(env);
}
