/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:52:53 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/19 19:52:54 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	draw_walls(t_sect *s)
{
	int 	i;
	int 	color;

	i = -1;
	color = C_WALL;
	while (++i < s->n_walls)
	{
		if (s->walls[i].is_portal)
			color = s->walls[i].is_door ? C_DOOR : C_PORTAL;
		draw_line(s->walls[i].v1, s->walls[i].v2, color);
	}
}

void 		draw_sector(t_ed *e)
{
	int 	i;

	i = -1;
	while (++i < e->n_sect)
		draw_walls(&e->seclist[i]);
}
