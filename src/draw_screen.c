/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 18:11:07 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/01 18:11:09 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

static void		init_draw_screen(t_draw *d, int num_sect, unsigned int ps)
{
	int 		i;

	d->head = &d->queue[0];
	d->tail = &d->queue[0];
	d->render_sec = (int*)malloc(sizeof(int) * num_sect);
	i = -1;
	while (++i < WIDTH)
	{
		d->ytop[i] = 0;
		d->ybot[i] = HEIGHT - 1;
	}
	i = -1;
	while (++i < num_sect)
		d->render_sec[i] = 0;
	*d->head = (t_item){ ps, 0, WIDTH - 1 };
	if(++(*d).head == (*d).queue + MAX_Q)
		d->head = d->queue;
}

static void		drender(t_draw *d, t_scene *s)
{
	int			i;

	d->now = d->tail;
	if (++(*d).tail == (*d).queue + MAX_Q)
		d->tail = d->queue;
	if (d->render_sec[d->now->sector_n] ^ 1)
		return ;
	d->sec = &s->sectors[d->now->sector_n];
	i = -1;
	while (++i < d->sec->npoints)
		draw_wall(d, s, i);
}

/*
 *
 */
void			draw_screen(t_scene *s)
{
	t_draw	d;

	init_draw_screen(&d, s->n_sectors, s->player.sector);
	while (d.head != d.tail)
		drender(&d, s);
}
