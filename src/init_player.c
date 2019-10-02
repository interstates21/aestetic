/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:06:18 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 16:18:28 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MINIMUM_HEIGHT 0.5

void	init_player3(t_data *d, t_player *player)
{
	player->speed_anim[M16] = 4;
	player->weapon_anim[M16][0] = 0;
	player->weapon_anim[M16][1] = 2;
	player->weapon_anim[M16][2] = 0;
	player->is_flying = 0;
	player->minimum_height = MINIMUM_HEIGHT;
	player->gravity = 0.0;
	player->can_move = 0;
	player->health = 100;
	player->can_be_stomped = 0;
	d->cursectnum = d->startsectnum;
	d->cam = d->startcam;
	d->cam.rot += 0.001;
	d->slot1 = NULL;
	d->slot2 = NULL;
	d->slot3 = NULL;
	d->weapon_type[BLASTER].current_ammo =
		d->weapon_type[BLASTER].max_ammo;
	d->weapon_type[CRYO_BALLISTA].current_ammo =
		d->weapon_type[CRYO_BALLISTA].max_ammo;
	d->weapon_type[M16].current_ammo =
		d->weapon_type[M16].max_ammo;
}

void	init_player2(t_data *d, t_player *player)
{
	player->speed_anim[BLASTER] = 6;
	player->weapon_anim[BLASTER][0] = 3;
	player->weapon_anim[BLASTER][1] = 2;
	player->weapon_anim[BLASTER][2] = 4;
	player->weapon_anim[BLASTER][3] = 0;
	player->weapon_anim[BLASTER][4] = 5;
	player->weapon_anim[BLASTER][5] = 6;
	player->weapon_anim[BLASTER][6] = 7;
	player->weapon_anim[BLASTER][7] = 8;
	player->weapon_anim[BLASTER][8] = 9;
	player->weapon_anim[BLASTER][9] = 10;
	player->weapon_anim[BLASTER][10] = 11;
	player->weapon_anim[BLASTER][11] = 12;
	player->weapon_anim[BLASTER][12] = 13;
	player->weapon_anim[BLASTER][13] = 14;
	player->weapon_anim[BLASTER][14] = 0;
	d->color_buf.value = 0;
	init_player3(d, player);
}

void	init_player(t_data *d, t_player *player)
{
	(void)d;
	ft_bzero(player, sizeof(*player));
	player->current_weapon = CRYO_BALLISTA;
	player->speed_anim[CRYO_BALLISTA] = 4;
	player->weapon_anim[CRYO_BALLISTA][0] = 0;
	player->weapon_anim[CRYO_BALLISTA][1] = 2;
	player->weapon_anim[CRYO_BALLISTA][2] = 3;
	player->weapon_anim[CRYO_BALLISTA][3] = 4;
	player->weapon_anim[CRYO_BALLISTA][4] = 5;
	player->weapon_anim[CRYO_BALLISTA][5] = 6;
	player->weapon_anim[CRYO_BALLISTA][6] = 7;
	player->weapon_anim[CRYO_BALLISTA][7] = 8;
	player->weapon_anim[CRYO_BALLISTA][8] = 9;
	player->weapon_anim[CRYO_BALLISTA][9] = 10;
	player->weapon_anim[CRYO_BALLISTA][10] = 11;
	player->weapon_anim[CRYO_BALLISTA][11] = 12;
	player->weapon_anim[CRYO_BALLISTA][12] = 0;
	init_player2(d, player);
}
