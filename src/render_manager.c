/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:44:00 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/28 15:44:01 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"

static void		draw_portal(t_scene *scene, t_draw *d, t_math *m, t_line l)
{
	t_line		n;

	n.pos.x = clamp((l.x - m->x[0]) * (m->prot[1].x - m->prot[0].x) /
	(m->x[1] - m->x[0]) + m->prot[0].x, d->top[l.x], d->bot[l.x]);
	n.pos.y = clamp((l.x - m->x[0]) * (m->prot[1].y - m->prot[0].y) /
	(m->x[1] - m->x[0]) + m->prot[0].y, d->top[l.x], d->bot[l.x]);
	n.light = 0x010101 * (255 - l.light);
	n.x = 0x040007 * (31 - l.light / 8);
	draw_line(scene, (t_scheme){l.x, l.pos.x, n.pos.x - 1, 0,
	l.x == m->x[0] || l.x == m->x[1] ? 0 : n.light, 0});
	d->top[l.x] = clamp(max(l.pos.x, n.pos.x), d->top[l.x], HEIGHT - 1);
	draw_line(scene, (t_scheme){l.x, n.pos.y + 1, l.pos.y, 0,
	l.x == m->x[0] || l.x == m->x[1] ? 0 : n.x, 0});
	d->bot[l.x] = clamp(min(l.pos.y, n.pos.y), 0, d->bot[l.x]);
}

static void		draw_wall(t_scene *scene, t_draw *d, t_math *m, int x)
{
	t_line		l;
	unsigned	r;

	l.x = x;
	l.light = ((x - m->x[0]) * (m->v2.y - m->v1.y) / (m->x[1] - m->x[0])
	+ m->v1.y) * 8;
	l.pos.x = clampi((x - m->x[0]) * (m->rot[1].x - m->rot[0].x) /
	(m->x[1] - m->x[0]) + m->rot[0].x, d->top[x], d->bot[x]);
	l.pos.y = clampi((x - m->x[0]) * (m->rot[1].y - m->rot[0].y) /
	(m->x[1] - m->x[0]) + m->rot[0].y, d->top[x], d->bot[x]);
	draw_line(scene,
	(t_scheme){l.x, d->top[x], l.pos.x - 1, 0x111111, 0x222222, 0x111111});
	draw_line(scene,
	(t_scheme){l.x, l.pos.y + 1, d->bot[x], 0x0000FF, 0x0000AA, 0x0000FF});
	if (d->portal >= 0)
	{
		draw_portal(scene, d, m, l);
		return ;
	}
	r = 0x010101 * (255 - l.light);
	draw_line(scene, (t_scheme){x, l.pos.x, l.pos.y, 0,
	x == m->x[0] || x == m->x[1] ? 0 : r, 0});
}

static int		clip_scale(t_scene *scene, t_draw *d, t_math *m)
{
	t_v2f		i1;
	t_v2f		i2;

	if (m->v1.y <= 0 || m->v2.y <= 0)
	{
		i1 = find_cross(m->v1, m->v2, scene->cam, -1);
		i2 = find_cross(m->v1, m->v2, scene->cam, 1);
		if (m->v1.y < scene->cam.n_z)
			m->v1 = i1.y > 0 ? i1 : i2;
		if (m->v2.y < scene->cam.n_z)
			m->v2 = i1.y > 0 ? i1 : i2;
	}
	m->scale[0] = (t_v2f){ HFOV / m->v1.y, VFOV / m->v1.y };
	m->x[0] = WIDTH / 2 - (int)(m->v1.x * m->scale[0].x);
	m->scale[1] = (t_v2f){ HFOV / m->v2.y, VFOV / m->v2.y };
	m->x[1] = WIDTH / 2 - (int)(m->v2.x * m->scale[1].x);
	return (m->x[0] >= m->x[1] || m->x[1] < d->cur.sx || m->x[0] > d->cur.sy);
}

static void		draw_world(t_scene *scene, t_draw *d)
{
	int			x;
	int			s;
	t_math		m;

	if (init_cycle(scene, d))
		return ;
	s = -1;
	while (++s < d->sec->npoints)
	{
		if (init_math(scene, d, &m, s) || clip_scale(scene, d, &m))
			continue ;
		d->portal = d->sec->portals[s];
		transform(scene, d, &m);
		d->range = (t_v2i){ maxi(m.x[0], d->cur.sx), mini(m.x[1], d->cur.sy) };
		x = d->range.x - 1;
		while (++x <= d->range.y)
			draw_wall(scene, d, &m, x);
		if (d->portal >= 0 && d->range.y >= d->range.x &&
			(d->head + MAX_Q + 1 - d->tail) % MAX_Q)
		{
			d->queue[d->head] = (t_queue){d->portal, d->range.x, d->range.y};
			d->head = d->head + 1 == MAX_Q ? 0 : d->head + 1;
		}
	}
}

void			render(t_scene *scene)
{
	t_draw		d;

	init_draw(scene, &d);
	draw_world(scene, &d);
	while (d.head != d.tail)
	{
		draw_world(scene, &d);
		++d.flags[d.cur.n_sector];
	}
}
