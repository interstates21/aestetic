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

void	init_contols(t_scene *scene)
{
	scene->player.move_speed = 0.05;
	scene->player.rot_speed = 2;
	scene->player.move_forw = 0;
	scene->player.move_back = 0;
	scene->player.rot_left = 0;
	scene->player.rot_right = 0;
}
