/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:34:11 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/24 17:34:12 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	draw_icon(t_ed *ed, t_v2 pos, int col)
{
	int i;
	int j;
	int size;

	size = 4;
	i = -size;
	while (i < size)
	{
		j = -size;
		while (j < size)
		{
			sdl_put_pix(&(ed->pixels), pos.x + j, pos.y + i, col);
			j++;
		}
		i++;
	}
}

void		render_env(t_ed *e)
{
	int		i;
	int		col;

	i = -1;
	while (++i < e->n_mns)
	{
		col = e->monsters[i].type == M_MELEE ? 0xfa7733 : 0xfa1199;
		draw_icon(e, e->monsters->pos, col);
	}
	i = -1;
	col = 0x55bf72;
	while (++i < e->n_sprt)
		draw_icon(e, e->sprt[i].pos, col);
}

void		add_sprite(t_ed *e)
{
	int		i;

	if (e->n_sprt == MAX_SPRT)
	{
		warn_me(e, "sprite number exceeded");
		return ;
	}
	i = e->n_sprt;
	e->n_sprt += 1;
	e->sprt[i].pos = e->controller.mouse;
	e->sprt[i].type = e->selection.sprite;
	e->sprt[i].secnum = e->selection.sector;
}

void		add_monster(t_ed *e)
{
	int		i;

	if (e->n_mns == MAX_MONS)
	{
		warn_me(e, "monster number exceeded");
		return ;
	}
	i = e->n_mns;
	e->n_mns += 1;
	e->monsters[i].pos = e->controller.mouse;
	e->monsters[i].type = e->selection.monster;
	e->monsters[i].secnum = e->selection.sector;
}
