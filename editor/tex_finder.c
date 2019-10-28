/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:36:54 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/25 17:36:55 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int			picking_sprite(t_v2 mouse, int n)
{
	int i;
	int offset;

	i = 0;
	while (i < n)
	{
		offset = i * 36;
		if (v2_compare(mouse, new_v2(FIRST_SPRITE_W + offset,
		FIRST_SPRITE_H), 28))
			return (i);
		i++;
	}
	return (-1);
}

int			picking_monster(t_v2 mouse)
{
	if (v2_compare(mouse, new_v2(MOSTER_1_PICKER_W, MOSTER_PICKER_H), 65))
		return (1);
	if (v2_compare(mouse, new_v2(MOSTER_2_PICKER_W, MOSTER_PICKER_H), 65))
		return (2);
	return (0);
}

void		find_used_tex(t_ed *e)
{
	int		j;
	int		i;

	e->used_tex = (char*)malloc(sizeof(char) * e->n_tex);
	j = -1;
	while (++j < e->n_tex)
		e->used_tex[j] = 0;
	j = -1;
	while (++j < e->n_sect && (i = -1))
	{
		e->used_tex[e->seclist[j].tex[T_FLOOR]] = 1;
		e->used_tex[e->seclist[j].tex[T_WALL]] = 1;
		e->used_tex[e->seclist[j].tex[T_CEIL]] = 1;
		while (++i < e->seclist[j].n_walls)
		{
			e->seclist[j].walls[i].tex[T_FLOOR] = e->seclist[j].tex[T_FLOOR];
			e->seclist[j].walls[i].tex[T_WALL] = e->seclist[j].tex[T_WALL];
			e->seclist[j].walls[i].tex[T_CEIL] = e->seclist[j].tex[T_CEIL];
		}
	}
	e->n_used_tex = 0;
	j = -1;
	while (++j < e->n_tex)
		e->n_used_tex += e->used_tex[j];
}
