/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:22:56 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 21:35:08 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	activate_neighbor_door(t_env *d, t_wall *door,
		t_wall *nextwall, t_sec *nei)
{
	int16_t last;
	int		i[2];
	t_vec2f a;
	t_vec2f b;

	last = nei->firstwallnum + nei->n_walls;
	i[0] = last - 1;
	i[1] = nei->firstwallnum;
	while (i[1] < last)
	{
		if (d->walls[i[0]].neighborsect >= 0)
		{
			a = d->walls[i[0]].point;
			b = d->walls[i[1]].point;
			if (a.x == nextwall->point.x && a.y == nextwall->point.y &&
					b.x == door->point.x && b.y == door->point.y)
			{
				d->door_active[i[0]] = d->door_active[door - d->walls];
				d->anim_door[i[0]] = d->anim_door[door - d->walls];
				return ((void)(d->walls[i[0]].key_num = 0));
			}
		}
		i[0] = i[1]++;
	}
}

void	br_msg(t_env *d, t_wall *w, int *n)
{
	d->anim_door[n[0]] = (d->door_active[n[0]] == 0 ||
			d->anim_door[n[0]] < 0) ? 0.01 : -0.01;
	play_sound(d, d->anim_door[n[0]] > 0 ? OPEN_DOOR_SOUND :
			CLOSE_DOOR_SOUND, v3_to_v2(d->cam.pos));
	activate_neighbor_door(d, &d->walls[n[0]], &d->walls[n[1]],
			&d->sectors[d->walls[n[0]].neighborsect]);
}

bool	door_use2(t_env *d, t_wall *w, int n[4])
{
	d->vslutiak = d->slot2;
	if (d->vslutiak && d->slot2->key_num == w->key_num && !(w->key_num = 0))
		d->vslutiak = NULL;
	else if (d->slot3 && d->slot3->key_num == w->key_num && !(w->key_num = 0))
		d->slot3 = NULL;
	br_msg(d, w, n);
	return (true);
}

bool	door_use(t_env *d, t_sec *sect)
{
	int		n[4];
	double	m[2];

	m[1] = INFINITY;
	n[2] = sect->firstwallnum + sect->n_walls - 1;
	n[3] = sect->firstwallnum;
	door_func(d, sect, n, m);
	if (m[1] == INFINITY)
		return (false);
	return (door_use2(d, &d->walls[n[0]], n));
}
