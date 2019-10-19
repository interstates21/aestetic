/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:25:54 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/19 19:25:55 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	part_2(t_ed *e)
{
	int 	v[4];

	v[0] = trim(ED_W >> 1, -1);
	v[1] = trim(ED_W >> 1, 1);
	v[2] = trim(ED_H >> 1, -1);
	v[3] = trim(ED_H >> 1, 1);
	e->seclist[0].walls[0] = (t_wall){ (t_v2){ v[1], v[2] },
	(t_v2){ v[1], v[3] }, 0, 0 };
	e->seclist[0].walls[1] = (t_wall){ (t_v2){ v[1], v[3] },
	(t_v2){ v[0], v[3] }, 0, 0 };
	e->seclist[0].walls[2] = (t_wall){ (t_v2){ v[0], v[3] },
	(t_v2){ v[0], v[2] }, 0, 0 };
	e->seclist[0].walls[3] = (t_wall){ (t_v2){ v[0], v[2] },
	(t_v2){ v[1], v[2] }, 0, 0 };
}

int 		trim(int point, int inc)
{
	while (point % GRID_GAP)
	{
		point += inc;
	}
	return (point);
}

void		init_sector(t_ed *e)
{
	e->n_sect = 1;
	e->seclist = (t_sect*)malloc(sizeof(t_sect));
	e->seclist[0].tex[T_FLOOR] = 0;
	e->seclist[0].tex[T_WALL] = 0;
	e->seclist[0].tex[T_CEIL] = 0;
	e->seclist[0].height[H_FLOOR] = 10;
	e->seclist[0].height[H_CEIL] = 50;
	e->seclist[0].is_dmg = 0;
	e->seclist[0].is_elev = 0;
	e->seclist[0].is_finish = 0;
	e->seclist[0].sprites = NULL;
	e->seclist[0].n_walls = 4;
	e->seclist[0].num = 0;
	e->seclist[0].slope[H_FLOOR] = 0;
	e->seclist[0].slope[H_CEIL] = 0;
	e->seclist[0].slope_rot[H_FLOOR] = 0;
	e->seclist[0].slope_rot[H_CEIL] = 0;
	e->seclist[0].n_walls = 4;
	e->seclist[0].walls = (t_wall*)malloc(sizeof(t_wall) * 4);
	part_2(e);
}
