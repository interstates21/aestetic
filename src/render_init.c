/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:49:33 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/28 15:49:34 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"

int				init_math(t_scene *s, t_draw *d, t_math *m, int k)
{
	t_v2f		tmp;

	tmp = (t_v2f){ d->sec->walls[k].x - d->player.pos.x,
	d->sec->walls[k].y - d->player.pos.y };
	m->v1 = (t_v2f){ tmp.x * d->player.anglesin - tmp.y * d->player.anglecos,
	tmp.x * d->player.anglecos + tmp.y * d->player.anglesin };
	tmp = (t_v2f){ d->sec->walls[k + 1].x - d->player.pos.x,
	d->sec->walls[k + 1].y - d->player.pos.y };
	m->v2 = (t_v2f){ tmp.x * d->player.anglesin - tmp.y * d->player.anglecos,
	tmp.x * d->player.anglecos + tmp.y * d->player.anglesin };
	return (m->v1.y <= 0 && m->v2.y <= 0);
}

void			transform(t_scene *s, t_draw *d, t_math *m)
{
	double		h[4];

	h[0] = d->sec->ceil - d->player.pos.z;
	h[1] = d->sec->floor - d->player.pos.z;
	h[2] = d->portal >= 0 ? s->sectors[d->portal].ceil - d->player.pos.z : 0;
	h[3] = d->portal >= 0 ? s->sectors[d->portal].floor - d->player.pos.z : 0;
	m->rot[0] = (t_v2i){
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v1.y, h[0]) * m->scale[0].y),
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v1.y, h[1]) * m->scale[0].y)};
	m->rot[1] = (t_v2i){
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v2.y, h[0]) * m->scale[1].y),
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v2.y, h[1]) * m->scale[1].y)};
	m->prot[0] = (t_v2i){
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v1.y, h[2]) * m->scale[0].y),
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v1.y, h[3]) * m->scale[0].y)};
	m->prot[1] = (t_v2i){
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v2.y, h[2]) * m->scale[1].y),
	HEIGHT / 2 - (int)(line_eq(d->player.yaw, m->v2.y, h[3]) * m->scale[1].y)};
}

void			init_draw(t_scene *s, t_draw *d)
{
	int			x;

	d->player = s->player;
	d->head = 0;
	d->tail = 0;
	d->flags = (int*)malloc(sizeof(int) * s->n_sectors);
	x = -1;
	while (++x < WIDTH)
	{
		d->bot[x] = HEIGHT - 1;
		d->top[x] = 0;
	}
	x = -1;
	while (++x < s->n_sectors)
		d->flags[x] = 0;
	d->queue[d->head] = (t_queue){d->player.sector, 0, WIDTH - 1};
	if (++d->head == MAX_Q)
		d->head = 0;
}

t_v2f			find_cross(t_v2f a, t_v2f b, t_cam c, int i)
{
	double		t[3];
	t_v2f		res;

	c.n_s = c.n_s * i;
	c.f_s = c.f_s * i;
	t[0] = xprod((t_v2f){ a.x - b.x, a.y - b.y},
	(t_v2f){ c.n_s - c.f_s, c.n_z - c.f_z });
	t[1] = xprod(a, b);
	t[2] = xprod((t_v2f){ c.n_s, c.n_z }, (t_v2f){ c.f_s, c.f_z });
	res.x = xprod((t_v2f){ t[1], a.x - b.x },
	(t_v2f){ t[2], c.n_s - c.f_s }) / t[0];
	res.y = xprod((t_v2f){ t[1], a.y - b.y },
	(t_v2f){ t[2], c.n_z - c.f_z }) / t[0];
	return (res);
}

int				init_cycle(t_scene *s, t_draw *d)
{
	d->cur = d->queue[d->tail];
	d->tail = d->tail + 1 == MAX_Q ? 0 : d->tail + 1;
	++d->flags[d->cur.n_sector];
	d->sec = &s->sectors[d->cur.n_sector];
	return (d->flags[d->cur.n_sector] & MAX_Q);
}
