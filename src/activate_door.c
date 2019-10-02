/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_activation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 13:25:48 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 18:04:58 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define ACTIVATION_DIST 3.0

void	activate_neighbor_door(t_data *d, t_wall *door,
		t_wall *nextwall, t_sector *nei)
{
	int16_t last;
	int		i;
	int		j;
	t_vec2f a;
	t_vec2f b;

	last = nei->firstwallnum + nei->numwalls;
	i = last - 1;
	j = nei->firstwallnum;
	while (j < last)
	{
		if (d->walls[i].neighborsect >= 0)
		{
			a = d->walls[i].point;
			b = d->walls[j].point;
			if (a.x == nextwall->point.x && a.y == nextwall->point.y &&
					b.x == door->point.x && b.y == door->point.y)
			{
				d->doorstate[i] = d->doorstate[door - d->walls];
				d->dooranimstep[i] = d->dooranimstep[door - d->walls];
				return ((void)(d->walls[i].key_num = 0));
			}
		}
		i = j++;
	}
}

double	get_dist(t_vec2f a, t_vec2f b, t_vec2f p)
{
	return (vec2f_length(sub_vec2f(p, get_closest(a, b, p))));
}

bool	activate_door2(t_data *d, t_wall *w, int n[4])
{
	if (d->slot1 && d->slot1->key_num == w->key_num && !(w->key_num = 0))
		d->slot1 = NULL;
	else if (d->slot2 && d->slot2->key_num == w->key_num && !(w->key_num = 0))
		d->slot2 = NULL;
	else if (d->slot3 && d->slot3->key_num == w->key_num && !(w->key_num = 0))
		d->slot3 = NULL;
	if (w->key_num)
	{
		invoke_msg(d, "YOU NEED A KEY");
		return (false);
	}
	d->dooranimstep[n[0]] = (d->doorstate[n[0]] == 0 ||
			d->dooranimstep[n[0]] < 0) ? 0.01 : -0.01;
	play_sound(d, d->dooranimstep[n[0]] > 0 ? OPEN_DOOR_SOUND :
			CLOSE_DOOR_SOUND, vec3to2(d->cam.pos));
	activate_neighbor_door(d, &d->walls[n[0]], &d->walls[n[1]],
			&d->sectors[d->walls[n[0]].neighborsect]);
	return (true);
}

bool	activate_door(t_data *d, t_sector *sect)
{
	int		n[4];
	double	m[2];

	m[1] = INFINITY;
	n[2] = sect->firstwallnum + sect->numwalls - 1;
	n[3] = sect->firstwallnum;
	while (n[3] < sect->firstwallnum + sect->numwalls)
	{
		if (d->walls[n[2]].is_door && d->walls[n[2]].neighborsect >= 0 &&
				(m[0] = get_dist(d->walls[n[2]].point, d->walls[n[3]].point,
				vec3to2(d->cam.pos))) < ACTIVATION_DIST && m[0] < m[1] &&
					(m[1] = m[0]) >= 0 &&
					(n[0] = n[2]) >= 0)
			n[1] = n[3];
		n[2] = n[3]++;
	}
	if (m[1] == INFINITY)
		return (false);
	return (activate_door2(d, &d->walls[n[0]], n));
}
