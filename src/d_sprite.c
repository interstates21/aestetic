/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_sprite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:07:52 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 19:20:07 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		draw_sprite(t_env *d, t_frustum *fr, t_sprite_list *sprite)
{
	if (sprite->type == IS_MONSTER)
		draw_monster(d, d->monsters[sprite->id]);
	if (sprite->type == IS_PROJECTILE)
		draw_proj(d, fr, d->anim_rots[sprite->id]);
}