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

void		find_used_tex(t_ed *e)
{
	int		j;
	int 	i;

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
