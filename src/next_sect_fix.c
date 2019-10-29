/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_sect_fix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:08:42 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:20:59 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static bool	is_part(t_v2_pair wall_vects, t_v2_pair vects, bool not_itself)
{
	bool	pos1;
	bool	pos2;

	pos1 = SAME_POS(wall_vects.v1, vects.v1);
	pos2 = SAME_POS(wall_vects.v2, vects.v2);
	return (pos1 && pos2 && not_itself);
}

static int	calculate_next_sect(t_env *d, t_range old_range, int old_current)
{
	int			current;
	t_v2_pair	p1;
	t_range		range;
	t_vec2f		v0;
	t_vec2f		v1;

	v0 = d->walls[old_range.max].point;
	v1 = d->walls[old_range.min].point;
	current = -1;
	while (++current < d->n_sect)
	{
		range = ranged_create(d->sectors[current].firstwallnum,
		d->sectors[current].firstwallnum + d->sectors[current].n_walls - 1);
		while (range.min < (d->sectors[current].firstwallnum +
												d->sectors[current].n_walls))
		{
			p1 = new_v2_pair(d->walls[range.max].point,
													d->walls[range.min].point);
			if (is_part(p1, new_v2_pair(v1, v0), current != old_current))
				return (current);
			range.max = range.min;
			range.min++;
		}
	}
	return (-1);
}

void		to_sector_load(t_env *d)
{
	int		current;
	int		min;
	int		max;
	int		sum;
	t_range range;

	range.min = 0;
	range.max = 0;
	current = 0;
	while (current < d->n_sect)
	{
		max = d->sectors[current].firstwallnum +
											d->sectors[current].n_walls - 1;
		min = d->sectors[current].firstwallnum;
		sum = d->sectors[current].firstwallnum + d->sectors[current].n_walls;
		range = ranged_create(min, max);
		while (range.min < sum)
		{
			d->walls[range.max].neighborsect =
										calculate_next_sect(d, range, current);
			range.max = range.min;
			range.min++;
		}
		current++;
	}
}
