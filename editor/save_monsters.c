/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:59:07 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/25 18:59:08 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	save_me(t_ed *e, t_mnst *m)
{
	t_stdmonster	s;

	s = (t_stdmonster){(t_v2f){m->pos.x, m->pos.y}, (t_v2f){0.0, 0.0},
	0, m->n_sect, 0, 0, 0, 0, 1, 0, 0};
	if (write(e->fd, &s, sizeof(t_stdmonster)) < 0)
		print_err("saving monster failed");
}

static void	save_me_too(t_ed *e, t_sprt *m, int i)
{
	t_stdast		s;
	t_sprite		tmp;

	tmp = e->sprites[m->type];
	s = (t_stdast){i, m->type, (t_v2f){m->pos.x, m->pos.y}, tmp.pos == H_FLOOR,
	tmp.pos == H_CEIL, (t_smd){tmp.heal, tmp.dmg, tmp.ammo, 0, 0},
	tmp.interactive, tmp.autopick, tmp.collision, tmp.jetpack, tmp.key,
	0, 0};
	if (write(e->fd, &s, sizeof(t_stdast)) < 0)
		print_err("saving sprite failed");
}

void		write_sprites(t_ed *e)
{
	int		i;
	int		j;
	int16_t tmp;

	tmp = e->n_sprt;
	if (write(e->fd, &tmp, sizeof(int16_t)) < 0)
		print_err("saving n_sprites failed");
	if (!tmp)
		return ;
	i = -1;
	while (++i < e->n_sect)
	{
		if (write(e->fd, &e->seclist[i].n_sprt, sizeof(int)) < 0)
			print_err("saving sector.n_sprites failed");
		j = -1;
		while (++j < e->n_sprt)
			if (e->sprt[j].n_sect == i)
				save_me_too(e, &e->sprt[j], e->seclist[i].n_sprt);
	}
}

void		write_monsters(t_ed *e)
{
	int		i;
	int16_t tmp;

	tmp = e->n_mns;
	if (write(e->fd, &tmp, sizeof(int16_t)) < 0)
		print_err("saving n_monsters failed");
	i = -1;
	while (++i < e->n_mns)
		save_me(e, &e->monst[i]);
}
