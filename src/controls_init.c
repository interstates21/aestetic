/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:55:17 by bdeomin           #+#    #+#             */
/*   Updated: 2019/08/27 18:27:33 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"

void init_controller(t_controller *controller) {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    controller->move_forw = false;
    controller->move_back = false;
    controller->rot_left = false;
    controller->rot_right = false;
    controller->falling = true;
    controller->ground = false;
    controller->moving = false;
    controller->ducking = false;
    controller->yaw = 0;
}
