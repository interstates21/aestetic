/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:26:00 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/03 16:26:01 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

static void	vline(t_scene *s, t_line l)
{
	int 	i;

	l.y1 = CLAMP(l.y1, 0, HEIGHT - 1);
	l.y2 = CLAMP(l.y2, 0, HEIGHT - 1);
	if (l.y1 == l.y2)
		sdl_put_pix(&s->pixels, l.x, l.y1, l.c_mid);
	else if (l.y2 > l.y1)
	{
		sdl_put_pix(&s->pixels, l.x, l.y1, l.c_top);
		i = l.y1;
		while (++i < l.y2)
			sdl_put_pix(&s->pixels, l.x, i, l.c_mid);
		sdl_put_pix(&s->pixels, l.x, l.y2, l.c_bot);
	}
}

static void	draw_nghbr(t_scene *s, t_draw *d, t_math m, int x)
{
	int 	nya;
	int 	nyb;
	int		r1;
	int		r2;

	nya = (x - m.x1) * (m.ny2.x - m.ny1.x) / (m.x2 - m.x1) + m.ny1.x;
	nya = CLAMP(nya, d->ytop[x], d->ybot[x]);
	nyb = (x - m.x1) * (m.ny2.y - m.ny1.y) / (m.x2 - m.x1) + m.ny1.y;
	nyb = CLAMP(nyb, d->ytop[x], d->ybot[x]);
	r1 = 0x010101 * (255 - d->z);
	r2 = 0x040007 * (31 - d->z / 8);
	vline(s, (t_line){x, d->ya, nya - 1, 0,
	x == m.x1 || x == m.x2 ? 0 : r1, 0});
	d->ytop[x] = CLAMP(MAX(d->ya, nya), d->ytop[x], HEIGHT - 1);
	vline(s, (t_line){x, nyb + 1, d->yb, 0,
	x == m.x1 || x == m.x2 ? 0 : r2, 0});
	d->ybot[x] = CLAMP(MIN(d->yb, nyb), 0, d->ybot[x]);
}

void		render_wall(t_scene *s, t_draw *d, t_math m, int x)
{
	int 	ya;
	int 	yb;

	d->z = 8 * (int)((x - m.x1) * (m.t2.y - m.t1.y) / (m.x2 - m.x1) + m.t1.y);
	ya = (x - m.x1) * (m.y2.x - m.y1.x) / (m.x2 - m.x1) + m.y1.x;
	d->ya = CLAMP(ya, d->ytop[x], d->ybot[x]);
	yb = (x - m.x1) * (m.y2.y - m.y1.y) / (m.x2 - m.x1) + m.y1.y;
	d->yb = CLAMP(yb, d->ytop[x], d->ybot[x]);
	vline(s, (t_line){x, d->ytop[x], d->ya - 1, 0x111111, 0x222222, 0x111111});
	vline(s, (t_line){x, d->yb + 1, d->ybot[x], 0x0000FF, 0x0000AA, 0x0000FF});
	if (m.nghbr >= 0)
		draw_nghbr(s, d, m ,x);
	else
		vline(s, (t_line){x, ya, yb, 0,
		x == m.x1 || x == m.x2 ? 0 : 0x010101 * (255 - d->z)});
}
