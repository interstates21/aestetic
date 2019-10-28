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
	int		i;

	i = -1;
	while (++i < e->n_walls)
		if (wall_eq(wall, e->walls[i]))
			return (1);
	return (0);
}

static int	interwl(t_v2 l[2], t_ed *e)
{
	double	det;
	double	tmp[2];
	int		res;
	int		i;

	i = -1;
	res = 0;
	while (++i < e->n_walls)
	{
		det = (e->walls[i].v2.x - e->walls[i].v1.x) * (l[0].y - l[1].y) -
		(l[0].x - l[1].x) * (e->walls[i].v2.y - e->walls[i].v1.y);
		if (!det)
			return (0);
		tmp[0] = (e->walls[i].v1.y - e->walls[i].v2.y) *
		(l[0].x - e->walls[i].v1.x) + (e->walls[i].v2.x - e->walls[i].v1.x) *
		(l[0].y - e->walls[i].v1.y);
		tmp[1] = (l[0].y - l[1].y) * (l[0].x - e->walls[i].v1.x) +
		(l[1].x - l[0].x) * (l[0].y - e->walls[i].v1.y);
		if (in_range(tmp[0] / det) && in_range(tmp[1] / det))
			res += 1;
	}
	return (res);
}

static int	intrs(t_wall w, t_ed *e)
{
	t_v2		coords[2];
	int			i;
	int			sum;
	int			wal;

	coords[0] = w.v1;
	coords[1] = w.v2;
	i = -1;
	sum = 0;
	while (++i < e->n_sect)
		sum += intersects(coords, &e->seclist[i]);
	wal = interwl(coords, e) - 1;
	if (v2_cmp(*e->selection.other_vertex, w.v2) || e->n_walls == 0)
		return (0);
	return (sum + wal);
}

void		loop_creation(t_ed *e)
{
	t_wall	tmp;
	t_v2	trm;

	e->controller.mouse = trim_v2(e->controller.mouse);
	trm = trim_v2(e->controller.mouse);
	tmp = new_wall(e->selection.val.x, e->selection.val.y, trm.x, trm.y);
	if ((exists(tmp, e) || intrs(tmp, e)) && e->n_walls > 1)
		return ;
	render_map(e);
	wall_push(e, tmp.v1, tmp.v2, -1);
	if (v2_cmp(trm, *e->selection.other_vertex))
	{
		tmp = (t_wall){.v1 = (t_v2){tmp.v2.x, tmp.v2.y},
		.v2 = (t_v2){e->selection.selected_vertex->x,
		e->selection.selected_vertex->y},
		.is_portal = e->selection.sector, .is_door = 0 };
		wall_push(e, tmp.v1, tmp.v2, e->selection.sector);
		finish_sector(e);
		e->selection.drawing = 0;
		return ;
	}
	e->selection.val = e->controller.mouse;
}
