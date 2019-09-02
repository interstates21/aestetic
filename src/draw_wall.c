/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:13:40 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/02 15:13:41 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

static void		init_math(t_draw *d, t_scene *s, int k, t_math *m)
{
	m->v1 = (t_v2f){ d->sec->vertex[k].x - s->player.pos.x,
	d->sec->vertex[k].y - s->player.pos.y };
	m->v2 = (t_v2f){ d->sec->vertex[k + 1].x - s->player.pos.x,
	d->sec->vertex[k + 1].y - s->player.pos.y };
	m->pcos = s->player.anglecos;
	m->psin = s->player.anglesin;
	m->t1 = (t_v2f){ m->v1.x * m->psin - m->v1.y * m->pcos };
	m->t2 = (t_v2f){ m->v2.x * m->psin - m->v2.y * m->pcos };
}

#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

static t_v2f	intersect(t_math m, int p)
{
	t_v2f		r;

	r.x = x_prod((t_v2f){x_prod(m.t1, m.t2), m.t1.x - m.t2.x},
	(t_v2f){x_prod((t_v2f){p * NEAR_SIDE, NEAR_Z}, (t_v2f){p * FAR_SIDE, FAR_Z})}
	)
}

static void		part_behind(t_math *m)
{
	m->in1 = intersect(*m, -1);
	m->in1 = intersect(*m, 1);
}

void			draw_wall(t_draw *d, t_scene *s, int k)
{
	t_math	m;

	init_math(d, s, k, &m);
	if (m.t1.y <= 0 && m.t2.y <= 0)
		return ;
	if (m.t1.y <= 0 && m.t2.y <= 0)
		part_behind(&m);
}
