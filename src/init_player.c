/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:17:11 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 17:24:19 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	init_player_2(t_env *d, t_player *player)
{
	d->pxls.value = 0;
	player->flying = 0;
	player->min_h = MINIMUM_HEIGHT;
	player->gravity = 0.0;
	player->moving = 0;
	player->health = 100;
	player->can_be_stomped = 1;
	d->this_sect = d->sect_begin;
	d->cam = d->startcam;
	d->cam.rot += 0.001;
	d->weapon_type.current_ammo = MAX_BULLETS;
}

void	play_initialization(t_env *d, t_player *player)
{
	int i;

	i = 1;
	ft_bzero(player, sizeof(*player));
	player->curr_weap = CRYO_BALLISTA;
	player->anim_speed[CRYO_BALLISTA] = 4;
	player->anim_weap[CRYO_BALLISTA][0] = 0;
	while (i < 12)
	{
		player->anim_weap[CRYO_BALLISTA][i] = i + 1;
		i++;
	}
	player->anim_weap[CRYO_BALLISTA][12] = 0;
	init_player_2(d, player);
}
