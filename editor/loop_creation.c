/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:15:33 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/20 19:15:34 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static int	exists(t_wall wall, t_ed *e)
{
	int 	i;

	i = -1;
	while (++i < e->n_walls)
		if (wall_eq(wall, e->walls[i]))
			return (1);
	return (0);
}

void		loop_creation(t_ed *e)
{
	t_wall	tmp;
	t_v2	trm;

	e->controller.mouse = trim_v2(e->controller.mouse);
	trm = trim_v2(e->controller.mouse);
	tmp = new_wall(e->selection.val.x, e->selection.val.y, trm.x, trm.y);
	if (exists(tmp, e))
		return;
	render_map(e);
	wall_push(e, tmp.v1, tmp.v2);
	if (v2_cmp(trm, *e->selection.other_vertex))
	{
		tmp = new_wall(tmp.v2.x, tmp.v2.y, e->selection.selected_vertex->x,
					   e->selection.selected_vertex->y);
		wall_push(e, tmp.v1, tmp.v2);
		finish_sector(e, e->selection.port);
		e->selection.drawing = 0;
		return ;
	}
	e->selection.val = e->controller.mouse;
}
