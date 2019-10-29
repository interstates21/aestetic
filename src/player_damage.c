/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_damage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:50:07 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:28:34 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	play_active(t_env *d)
{
	d->player.min_h = MINIMUM_CROUCH_HEIGHT;
	d->player.gravity = fabs(d->player.gravity);
	buf_to_collor2(d, d->player.gravity * 100, 0x111111);
	if (d->player.gravity > 0.2)
		d->player.moving = 40;
	else
		d->player.moving = 20;
	d->player.gravity = 0.0;
	d->player.health -= 10;
	if (d->player.health > 0)
		play_sound(d, PLAYER_FELL_SOUND, v3_to_v2(d->cam.pos));
}

void	proj_to_hit_play(t_env *d, t_anim_rot *proj)
{
	buf_to_collor2(d, d->anim_rot_type[proj->id_type].damage, RED);
	if (proj)
		to_ch_iter(d, atan2(proj->dir.z,
					proj->dir.x), BOUNCING_DIST_PROJ);
	d->player.health -= d->anim_rot_type[proj->id_type].damage;
	play_sound(d, PLAYER_GOT_HIT_SOUND, v3_to_v2(d->cam.pos));
}

void	view_danget_stash(t_env *d)
{
	double	h_area;

	h_area = d->cam.pos.y - d->player.min_h - d->player_floor_h;
	if (!d->sectors[d->this_sect].is_harmful || fabs(h_area) > 0.1 ||
					SDL_GetTicks() - d->harmful_area < 1000)
		return ;
	buf_to_collor2(d, 7, RED);
	d->player.health -= 20;
	d->harmful_area = SDL_GetTicks();
	if (d->player.health > 0)
		play_sound(d, PLAYER_GOT_HIT_SOUND, v3_to_v2(d->cam.pos));
}

void	play_and_monst_acive(t_env *d, t_monster *monster)
{
	if (monster->id_type == MOTHERDEMON || monster->id_type == CHARGINGDEMON)
	{
		if (!d->player.can_be_stomped)
		{
			if (monster->id_type == MOTHERDEMON)
				d->player.health -= 10;
			else if (monster->id_type == CHARGINGDEMON)
				d->player.health -= 20;
			d->player.can_be_stomped = 30;
			monster->id_type == MOTHERDEMON ? buf_to_collor2(d, 5, RED) :
												buf_to_collor2(d, 8, RED);
			if (d->player.health > 0)
			{
				monster->id_type == CHARGINGDEMON ?
						play_sound(d, CHARG_ATK_SOUND, monster->pos) : true;
				play_sound(d, PLAYER_FELL_SOUND, v3_to_v2(d->cam.pos));
			}
		}
		to_ch_iter(d, atan2(monster->dir.y, monster->dir.x),
				BOUNCING_DIST_MOTHERDEMON);
		monster->id_type == CHARGINGDEMON ? dellay_char_demyon(monster) : true;
	}
}
