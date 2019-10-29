/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:18:35 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 21:18:36 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	first_sin(t_env *env, short k, bool sin)
{
	int16_t	ups;

	ups = 0;
	if (!sin && ((ups = second_sin(env, k))) >= 0)
	{
		if (ups != env->anim_rots[k].this_sect)
			list_swp(IS_PROJECTILE, k, env,
			(int[2]){env->anim_rots[k].this_sect, ups});
		env->anim_rots[k].this_sect = ups;
		new_proj_animate(&env->anim_rots[k], env, k, sin);
	}
	else
		ups == -2 ? third_sin(env, k)
		: new_proj_animate(&env->anim_rots[k], env, k, true);
}

int16_t		second_sin(t_env *env, short k)
{
	int16_t	res;
	int16_t	t[2];

	t[0] = env->anim_rots[k].this_sect;
	t[1] = -1;
	res = new_proj_curs(t, env, NB_OF_SECTOR_DEPTH,
	env->anim_rots[k].pos);
	return (res);
}

void		third_sin(t_env *env, short k)
{
	env->anim_rots[k].is_active = 0;
	mailing_deleted(k, &env->sectors[env->anim_rots[k].this_sect],
	IS_PROJECTILE);
}

void		fourth_sin(t_env *env, short k)
{
	char	sin;

	sin = env->anim_rot_type[env->anim_rots[k].id_type].threat_to_monster
	? proj_monst_colided(env, &env->sectors[env->anim_rots[k].this_sect],
	&env->anim_rots[k]) : 0;
	sin = env->anim_rot_type[env->anim_rots[k].id_type].threat_to_player
	? proj_play_colided(env, &env->anim_rots[k]) : sin;
	first_sin(env, k, sin);
}

void		fifth_sin(t_env *env, short *k)
{
	new_proj_animate(&env->anim_rots[*k], env, *k, 0);
	*k += 1;
}
