/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:22:56 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 14:13:12 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	activate_neighbor_door(t_data *d, t_wall *door,
		t_wall *nextwall, t_sector *nei)
{
	int16_t last;
	int		i[2];
	t_vec2f a;
	t_vec2f b;

	last = nei->firstwallnum + nei->numwalls;
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
				d->doorstate[i[0]] = d->doorstate[door - d->walls];
				d->dooranimstep[i[0]] = d->dooranimstep[door - d->walls];
				return ((void)(d->walls[i[0]].key_num = 0));
			}
		}
		i[0] = i[1]++;
	}
}

void	br_msg(t_data *d, t_wall *w, int *n)
{
	d->dooranimstep[n[0]] = (d->doorstate[n[0]] == 0 ||
			d->dooranimstep[n[0]] < 0) ? 0.01 : -0.01;
	play_sound(d, d->dooranimstep[n[0]] > 0 ? OPEN_DOOR_SOUND :
			CLOSE_DOOR_SOUND, v3_to_v2(d->cam.pos));
	activate_neighbor_door(d, &d->walls[n[0]], &d->walls[n[1]],
			&d->sectors[d->walls[n[0]].neighborsect]);
}

bool	activate_door2(t_data *d, t_wall *w, int n[4])
{
	br_msg(d, w, n);
	return (true);
}

bool	activate_door(t_data *d, t_sector *sect)
{
	int		n[4];
	double	m[2];

	m[1] = INFINITY;
	n[2] = sect->firstwallnum + sect->numwalls - 1;
	n[3] = sect->firstwallnum;

	whi_le(d, sect, n, m);
	if (m[1] == INFINITY)
		return (false);
	return (activate_door2(d, &d->walls[n[0]], n));
}
