/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:17:00 by akolomoi          #+#    #+#             */
/*   Updated: 2019/08/21 17:17:01 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

// сцена нужна для проверки по секторам
int		player_init(t_scene *s, t_v2f pos, double ang, unsigned int sect)
{
	if (sect >= s->sectors_total)
		return (0);
	s->player.angle = ang;
	s->player.sector = sect;
	s->player.pos = (t_v3f){ pos.x, pos.y, s->sectors[sect].floor + EYE_HEIGHT};
	s->player.anglecos = 0.0;
	s->player.anglesin = 0.0;
	s->player.motion = (t_v3f){ 0.0, 0.0, 0.0 };
	s->player.yaw = 0.0;
	s->player.move_speed = 0.0;
	s->player.rot_speed = 0.0;
	return (1);
}
