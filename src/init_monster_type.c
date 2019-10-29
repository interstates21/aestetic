/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monster_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:16:29 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:17:04 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

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
