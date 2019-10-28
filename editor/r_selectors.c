/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_selectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:42:23 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:42:24 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		store_selected(t_ed *ed, t_wall *w, t_v2 *v)
{
	ed->selection.selected_vertex = v;
	ed->selection.val = *v;
	ed->selection.selected_wall = w;
	ed->selection.other_vertex = v == &w->v1 ? &w->v2 : &w->v1;
}

static void	tell_em_im_here(t_ed *e)
{
	int		i;
	int		j;

	i = -1;
	while (++i < e->selection.selected_wall->is_portal)
		;
	j = -1;
	while (++j < e->seclist[i].n_walls)
		if (e->seclist[i].walls[j].is_portal == e->selection.sector)
		{
			e->seclist[i].walls[j].is_door =
			e->seclist[i].walls[j].is_door ? 0 : 1;
			return ;
		}
}

static int	gut_check(t_ed *e)
{
	int		i;

	i = -1;
	if (e->selection.selected_wall->is_portal > -1)
	{
		e->selection.selected_wall->is_door =
		e->selection.selected_wall->is_door ? 0 : 1;
		while (++i < e->n_sect)
			tell_em_im_here(e);
		e->selection = (t_selection){ .selected_vertex = NULL,
		.selected_wall = NULL, .drawing = 0};
		return (0);
	}
	return (1);
}

t_bool		sector_selected(t_ed *ed)
{
	int		i;
	int		k;

	i = -1;
	while (++i < ed->n_sect && (k = -1))
		while (++k < ed->seclist[i].n_walls)
			if (v2_compare(ed->seclist[i].walls[k].v1,
			ed->controller.mouse, SELECTION_FIELD))
			{
				store_selected(ed, &(ed->seclist[i].walls[k]),
				&(ed->seclist[i].walls[k].v1));
				ed->selection.drawing = 1;
				ed->selection.port = i;
				return (gut_check(ed));
			}
			else if (v2_compare(ed->seclist[i].walls[k].v2,
			ed->controller.mouse, SELECTION_FIELD))
				store_selected(ed, &(ed->seclist[i].walls[k]),
				&(ed->seclist[i].walls[k].v2));
	ed->selection.drawing = 0;
	return (false);
}

t_bool		corner_selected(t_ed *ed)
{
	return (sector_selected(ed));
}
