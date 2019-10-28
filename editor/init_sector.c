/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:08:55 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/20 17:08:56 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_sect		init_sector(t_wall **walls, int n_walls, int n_s)
{
	t_sect res;

	res = (t_sect){.num = n_s - 1, .height[H_CEIL] = 20, .height[H_FLOOR] = 10,
	.tex[T_FLOOR] = 0, .tex[T_WALL] = 0, .tex[T_CEIL] = 0, .n_walls = n_walls,
	.is_dmg = 0, .is_elev = 0, .is_finish = 0, .slope[H_FLOOR] = 0,
	.slope[H_CEIL] = 0, .slope_rot[H_FLOOR] = 0, .slope_rot[H_CEIL] = 0,
	.start_wall = 0};
	res.walls = *walls;
	return (res);
}

void		init_default_sect(t_ed *e)
{
	t_wall	*walls;

	e->n_sect = 1;
	e->seclist = (t_sect*)malloc(sizeof(t_sect));
	walls = (t_wall*)malloc(sizeof(t_wall) * 4);
	walls[0] = (t_wall){.is_door = 0, .is_portal = -1,
	.v1 = (t_v2){ trim(ED_W >> 1, 1), trim(ED_H >> 1, 1) },
	.v2 = (t_v2){ trim(ED_W >> 1, 1), trim(ED_H >> 1, -1) }};
	walls[1] = (t_wall){.is_door = 0, .is_portal = -1,
	.v1 = (t_v2){ trim(ED_W >> 1, 1), trim(ED_H >> 1, -1) },
	.v2 = (t_v2){ trim(ED_W >> 1, -1), trim(ED_H >> 1, -1) }};
	walls[2] = (t_wall){.is_door = 0, .is_portal = -1,
	.v1 = (t_v2){ trim(ED_W >> 1, -1), trim(ED_H >> 1, -1) },
	.v2 = (t_v2){ trim(ED_W >> 1, -1), trim(ED_H >> 1, 1) }};
	walls[3] = (t_wall){.is_door = 0, .is_portal = -1,
	.v1 = (t_v2){ trim(ED_W >> 1, -1), trim(ED_H >> 1, 1) },
	.v2 = (t_v2){ trim(ED_W >> 1, 1), trim(ED_H >> 1, 1) }};
	e->n_all_w = 4;
	e->seclist[0] = init_sector(&walls, 4, e->n_sect - 1);
}
