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

static void	vline(t_line p, )

void		render_wall(t_scene *s, t_draw *d, t_math m, int x)
{
	int 	z;
	int 	ya;
	int 	yb;

	z = 8 * (int)((x - m.x1) * (m.t2.y - m.t1.y) / (m.x2 - m.x1) + m.t2.y);
	ya = (x - m.x1) * (m.y2.x - m.y1.x) / (m.x2 - m.x1) + m.y1.x;
	ya = CLAMP(ya, d->ytop[x], d->ybot[x]);
	yb = (x - m.x1) * (m.y2.y - m.y1.y) / (m.x2 - m.x1) + m.y1.y;
	yb = CLAMP(yb, d->ytop[x], d->ybot[x]);
	vline();
}
