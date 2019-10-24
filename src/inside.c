/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 20:06:16 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	inside(t_data *d, int16_t sectnum, t_vec2f pos)
{
	int		rz[5];
	t_vec2f	bon0;
	t_vec2f	bon2;

	rz[0] = 0;
	rz[1] = d->sectors[sectnum].numwalls;
	rz[2] = 0;
	rz[3] = rz[1] - 1;
	while (rz[2] < rz[1])
	{
		bon0 = d->walls[d->sectors[sectnum].firstwallnum + rz[2]].point;
		bon2 = d->walls[d->sectors[sectnum].firstwallnum + rz[3]].point;
		if (((bon0.y > pos.y) != (bon2.y > pos.y)) &&
				(pos.x < (bon2.x - bon0.x) * (pos.y - bon0.y) / (bon2.y - bon0.y) + bon0.x))
			rz[0] = !rz[0];
		rz[3] = rz[2]++;
	}
	return (rz[0]);
}

int16_t	search_other_sectors(int16_t sects[2], t_data *d, int depth,
		t_vec3f pos)
{
	short	i;
	short	j;
	short	ret_value;

	i = d->sectors[sects[0]].firstwallnum - 1;
	j = d->sectors[sects[0]].firstwallnum +
		d->sectors[sects[0]].numwalls;
	while (++i < j)
		if (d->walls[i].neighborsect != -1 && d->walls[i].neighborsect !=
				sects[1] && d->doorstate[i] > 0.7)
			if ((ret_value = update_cursect_proj((int16_t[2]){d->walls[i].
							neighborsect, sects[0]}, d, depth - 1, pos)) != -1)
				return (ret_value);
	if (sects[1] == -1 && d->sectors[sects[0]].outdoor &&
			pos.y > d->sectors[sects[0]].ceilheight + DIST_COLL_PROJ_CEIL_FLOOR)
		return (-2);
	return (-1);
}

int16_t	update_cursect_proj(int16_t sects[2], t_data *d, int depth,
		t_vec3f pos)
{
	double	floor_height;
	double	ceil_height;

	floor_height = get_floor_height(&d->sectors[sects[0]], d->walls,
													sects[0], v3_to_v2(pos));
	ceil_height = get_ceil_height(&d->sectors[sects[0]], d->walls,
													sects[0], v3_to_v2(pos));
	if (inside(d, sects[0], (t_vec2f){pos.x, pos.z}) &&
			(pos.y < ceil_height || d->sectors[sects[0]].outdoor) &&
			pos.y > floor_height)
		return (sects[0]);
	if (!depth)
		return (-1);
	return (search_other_sectors(sects, d, depth, pos));
}

int16_t	update_cursect_smart(t_data *d, short depth, t_vec2f pos,
		uint16_t cursectnum)
{
	short	i;
	short	tab[MAXNUMSECTORS];
	short	tmp_tab[MAXNUMSECTORS];

	ft_memset(tab, -1, sizeof(tab));
	ft_memset(tmp_tab, -1, sizeof(tmp_tab));
	tab[0] = cursectnum;
	while (depth)
	{
		i = 0;
		while (tab[i] != -1)
		{
			if (inside(d, tab[i], pos))
				return (tab[i]);
			set_tab(d, tab[i], &tmp_tab[0], tab[i]);
			i++;
		}
		swap_tabs(&tab[0], &tmp_tab[0]);
		depth--;
	}
	return (-1);
}
