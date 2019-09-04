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
	m->t1 = (t_v2f){ m->v1.x * m->psin - m->v1.y * m->pcos,
	m->v1.x * m->pcos + m->v1.y * m->psin};
	m->t2 = (t_v2f){ m->v2.x * m->psin - m->v2.y * m->pcos,
	m->v2.x * m->pcos + m->v2.y * m->psin};
	m->nyceil = 0;
	m->nyfloor = 0;
}

/*
 * #define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
 * vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
 * vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })
 *
 * x-x
 */

static t_v2f	intersect(t_math m, int p)
{
	return ((t_v2f){
	(x_prod((t_v2f){ x_prod(m.t1, m.t2), m.t1.x - m.t2.x },
	(t_v2f){ x_prod((t_v2f){ p * N_SIDE, N_Z}, (t_v2f){ p * F_SIDE, F_Z }),
	p * N_SIDE - p * F_SIDE })
	/ x_prod((t_v2f){ m.t1.x - m.t2.x, m.t1.y - m.t2.y },
	(t_v2f){ p * N_SIDE - p * F_SIDE, N_Z - F_Z })),
	(x_prod((t_v2f){ x_prod(m.t1, m.t2), m.t1.y - m.t2.y },
	(t_v2f){ x_prod((t_v2f){ p * N_SIDE, N_Z}, (t_v2f){ p * F_SIDE, F_Z }),
	N_Z - F_Z })
	/ x_prod((t_v2f){ m.t1.x - m.t2.x, m.t1.y - m.t2.y },
	(t_v2f){ p * N_SIDE - p * F_SIDE, N_Z - F_Z }))
	});
}

static void		part_behind(t_math *m)
{
	m->in1 = intersect(*m, -1);
	m->in2 = intersect(*m, 1);
	if (m->t1.y < N_Z)
	{
		m->t1.x = m->in1.y > 0 ? m->in1.x : m->in2.x;
		m->t1.y = m->in1.y > 0 ? m->in1.y : m->in2.y;
	}
	if (m->t2.y < N_Z)
	{
		m->t2.x = m->in1.y > 0 ? m->in1.x : m->in2.x;
		m->t2.y = m->in1.y > 0 ? m->in1.y : m->in2.y;
	}
}

static int		math2(t_math *m, t_scene *s, t_draw *d, int k)
{
	m->scale1 = (t_v2f){H_FOV / m->t1.y, V_FOV / m->t1.y};
	m->x1 = WIDTH / 2 - (int)(m->t1.x * m->scale1.x);
	m->scale2 = (t_v2f){H_FOV / m->t2.y, V_FOV / m->t2.y};
	m->x2 = WIDTH / 2 - (int)(m->t2.x * m->scale2.x);
	if (m->x1 >= m->x2 || m->x2 < d->now->sx1 || m->x1 < d->now->sx2)
		return (1);
	m->y_ceil = d->sec->ceil - s->player.pos.z;
	m->y_ceil = d->sec->floor - s->player.pos.z;
	if ((m->nghbr = d->sec->portals[k]) >= 0)
	{
		m->nyceil = s->sectors[m->nghbr].ceil - s->player.pos.z;
		m->nyfloor = s->sectors[m->nghbr].floor - s->player.pos.z;
	}
	black_magic(m, s);
	m->begin = MAX(m->x1, d->now->sx1);
	m->end = MIN(m->x2, d->now->sx2);
	return (0);
}

void			draw_wall(t_draw *d, t_scene *s, int k)
{
	t_math	m;
	int		i;

	init_math(d, s, k, &m);
	if (m.t1.y <= 0 && m.t2.y <= 0)
		return ;
	if (m.t1.y <= 0 && m.t2.y <= 0)
		part_behind(&m);
	if (math2(&m, s, d, k))
		return ;
	i = m.begin - 1;
	while (++i <= m.end)
		render_wall(s, d, m, i);
	if (m.nghbr >= 0 && m.end>= m.begin &&
	(d->head + MAX_Q + 1 - d->tail) % MAX_Q)
	{
		*d->head = (t_item){m.nghbr, m.begin, m.end};
		if (++d->head == d->queue + MAX_Q)
			d->head = d->queue;
	}
}
