/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_damage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:50:07 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 03:08:25 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	player_fell(t_data *d)
{
	d->player.minimum_height = MINIMUM_CROUCH_HEIGHT;
	d->player.gravity = fabs(d->player.gravity);
	change_buf_colo(d, d->player.gravity * 100, 0x111111);
	if (d->player.gravity > 0.2)
		d->player.can_move = 40;
	else
		d->player.can_move = 20;
	d->player.gravity = 0.0;
	d->player.health -= 10;
	if (d->player.health > 0)
		play_sound(d, PLAYER_FELL_SOUND, v3_to_v2(d->cam.pos));
}

void	player_hit_proj(t_data *d, t_projectile *proj)
{
	change_buf_colo(d, d->projectile_type[proj->id_type].damage, RED);
	if (proj)
		change_inertia(d, atan2(proj->dir.z,
					proj->dir.x), BOUNCING_DIST_PROJ);
	d->player.health -= d->projectile_type[proj->id_type].damage;
	play_sound(d, PLAYER_GOT_HIT_SOUND, v3_to_v2(d->cam.pos));
}

void	check_dangerous_area(t_data *d)
{
	double	h_area;

	h_area = d->cam.pos.y - d->player.minimum_height - d->floorheightplayer;
	if (!d->sectors[d->cursectnum].is_harmful || fabs(h_area) > 0.1 ||
					SDL_GetTicks() - d->last_dangerous_area_damage < 1000)
		return ;
	change_buf_colo(d, 7, RED);
	d->player.health -= 20;
	d->last_dangerous_area_damage = SDL_GetTicks();
	if (d->player.health > 0)
		play_sound(d, PLAYER_GOT_HIT_SOUND, v3_to_v2(d->cam.pos));
}

void	contact_with_monster(t_data *d, t_monster *monster)
{
	if (monster->id_type == MOTHERDEMON || monster->id_type == CHARGINGDEMON)
	{
		if (!d->player.can_be_stomped)
		{
			if (monster->id_type == MOTHERDEMON)
				d->player.health -= d->difficulty == HARD ? 10 : 5;
			else if (monster->id_type == CHARGINGDEMON)
				d->player.health -= d->difficulty == HARD ? 20 : 15;
			d->player.can_be_stomped = 30;
			monster->id_type == MOTHERDEMON ? change_buf_colo(d, 5, RED) :
												change_buf_colo(d, 8, RED);
			if (d->player.health > 0)
			{
				monster->id_type == CHARGINGDEMON ?
						play_sound(d, CHARG_ATK_SOUND, monster->pos) : true;
				play_sound(d, PLAYER_FELL_SOUND, v3_to_v2(d->cam.pos));
			}
		}
		change_inertia(d, atan2(monster->dir.y, monster->dir.x),
				BOUNCING_DIST_MOTHERDEMON);
		monster->id_type == CHARGINGDEMON ? charging_demon_wait(monster) : true;
	}
}
