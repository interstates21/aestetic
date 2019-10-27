/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_shoot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:03:45 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 03:08:27 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void handle_click(t_data *e) {
    int             ammo;;
    u_int8_t        weapon;
    t_vec2f         cam_proj;

    ammo = e->weapon_type.current_ammo;
    weapon = e->player.current_weapon;
    cam_proj = v3_to_v2(e->cam.pos);
	if (e->left_mouse_button == MOUSE_PRESSED)
	{
        if (!ammo) {
            invoke_msg(e, "Don't have patrons = (((");
            return ;
        }
        play_sound(e, CRYO_SOUND, cam_proj);
		e->player.click = 1;
		e->player.can_shoot = e->weapon_type.rate_of_fire[0];
		e->player.current_anim_playing = F_ANIM;
		e->player.timer_anim_weap = e->player.speed_anim[weapon];
	}
}