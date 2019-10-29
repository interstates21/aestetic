/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 17:28:45 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	del_mem_spr(t_env *d, short i)
{
	t_sprite_list	*list;
	t_sprite_list	*need_free;

	list = d->sectors[i].sprite_list;
	d->sectors[i].sprite_list = NULL;
	while (list)
	{
		need_free = list->next;
		free(list);
		list = need_free;
	}
}

bool	inside(t_env *d, int16_t sectnum, t_vec2f pos)
{
	int		rz[5];
	t_vec2f	bon0;
	t_vec2f	bon2;

	rz[0] = 0;
	rz[1] = d->sectors[sectnum].n_walls;
	rz[2] = 0;
	rz[3] = rz[1] - 1;
	while (rz[2] < rz[1])
	{
		bon0 = d->walls[d->sectors[sectnum].firstwallnum + rz[2]].point;
		bon2 = d->walls[d->sectors[sectnum].firstwallnum + rz[3]].point;
		if (((bon0.y > pos.y) != (bon2.y > pos.y)) &&
			(pos.x < (bon2.x - bon0.x) * (pos.y - bon0.y) / (bon2.y - bon0.y)
																	+ bon0.x))
			rz[0] = !rz[0];
		rz[3] = rz[2]++;
	}
	return (rz[0]);
}

int16_t	search_other_sectors(int16_t sects[2], t_env *d, int depth,
		t_vec3f pos)
{
	short	i;
	short	j;
	short	ret_value;

	i = d->sectors[sects[0]].firstwallnum - 1;
	j = d->sectors[sects[0]].firstwallnum +
		d->sectors[sects[0]].n_walls;
	while (++i < j)
		if (d->walls[i].neighborsect != -1 && d->walls[i].neighborsect !=
				sects[1] && d->door_active[i] > 0.7)
			if ((ret_value = new_proj_curs((int16_t[2]){d->walls[i].
							neighborsect, sects[0]}, d, depth - 1, pos)) != -1)
				return (ret_value);
	if (sects[1] == -1 && d->sectors[sects[0]].outdoor &&
			pos.y > d->sectors[sects[0]].ceilheight + DIST_COLL_PROJ_CEIL_FLOOR)
		return (-2);
	return (-1);
}

int16_t	new_proj_curs(int16_t sects[2], t_env *d, int depth,
		t_vec3f pos)
{
	double	floor_height;
	double	ceil_height;

	floor_height = height_fl_val(&d->sectors[sects[0]], d->walls,
													sects[0], v3_to_v2(pos));
	ceil_height = height_cl_val(&d->sectors[sects[0]], d->walls,
													sects[0], v3_to_v2(pos));
	if (inside(d, sects[0], new_v2(pos.x, pos.z)) &&
			(pos.y < ceil_height || d->sectors[sects[0]].outdoor) &&
			pos.y > floor_height)
		return (sects[0]);
	if (!depth)
		return (-1);
	return (search_other_sectors(sects, d, depth, pos));
}

int16_t	new_smart_curs(t_env *d, short depth, t_vec2f pos,
		uint16_t this_sect)
{
	short	i;
	short	tab[N_SECTORS];
	short	tmp_tab[N_SECTORS];

	ft_memset(tab, -1, sizeof(tab));
	ft_memset(tmp_tab, -1, sizeof(tmp_tab));
	tab[0] = this_sect;
	while (depth)
	{
		i = 0;
		while (tab[i] != -1)
		{
			if (inside(d, tab[i], pos))
				return (tab[i]);
			tab_new(d, tab[i], &tmp_tab[0], tab[i]);
			i++;
		}
		tabulation_sw(&tab[0], &tmp_tab[0]);
		depth--;
	}
	return (-1);
}
