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

void handle_click(t_env *e) {
    int             ammo;;
    u_int8_t        weapon;
    t_vec2f         cam_proj;

    ammo = e->weapon_type.current_ammo;
    weapon = e->player.curr_weap;
    cam_proj = v3_to_v2(e->cam.pos);
	if (e->left_mouse_button == MOUSE_PRESSED)
	{
        if (!ammo) {
            invoke_msg(e, "Don't have patrons = (((");
            return ;
        }
        play_sound(e, CRYO_SOUND, cam_proj);
		e->player.click = 1;
		e->player.shooting = e->weapon_type.rate_of_fire[0];
		e->player.is_curr_anim = F_ANIM;
		e->player.time_anim_weapon = e->player.anim_speed[weapon];
	}
}