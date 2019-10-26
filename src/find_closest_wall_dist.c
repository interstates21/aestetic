/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_wall_dist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:29:19 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/25 22:42:00 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	new_closest_wall(t_data *d, t_vec2f *position, short *j,
		uint16_t sect_to_scan)
{
	*position = new_v2(d->cam.pos.x + 100000 * d->cam.sin,
		d->cam.pos.z + 100000 * d->cam.cos);
	*j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls - 1;
}

static void	new_dist_of_sector(t_data *d, double *dist, t_vec2f sector)
{
	double		value;

	value = v2_dot(v2_min(v3_to_v2(d->cam.pos), sector));
	(*dist > value || *dist != -1) ? true : (*dist = value);
}

t_vec2f		checking_walls(t_data *d, t_vec2 i_j, t_vec2f position,
															t_vec2f sector)
{
	if (d->walls[i_j.y].neighborsect == -1 || d->doorstate[i_j.y] < 0.7)
	{
		sector = intersect(v3_to_v2(d->cam.pos),
			position, d->walls[i_j.y].point, d->walls[i_j.x].point);
		if (sector.x != -1 && sector.y != -1 && is_inside_vec2f(
						d->walls[i_j.y].point, d->walls[i_j.x].point, sector)
				&& is_inside_vec2f(v3_to_v2(d->cam.pos), position, sector))
			return (new_v2(sector.x, sector.y));
	}
	return (new_v2(-1, -1));
}

double		find_closest_wall_dist(t_data *d, uint16_t sect_to_scan)
{
	short	i;
	short	j;
	double	dist;
	t_vec2f	position;
	t_vec2f	sector;

	dist = -1;
	new_closest_wall(d, &position, &j, sect_to_scan);
	i = d->sectors[sect_to_scan].firstwallnum;
	while (i < d->sectors[sect_to_scan].firstwallnum +
			d->sectors[sect_to_scan].numwalls)
	{
		sector = checking_walls(d, (t_vec2){i, j}, position, sector);
		if (sector.x != -1 && sector.y != -1)
			new_dist_of_sector(d, &dist, sector);
		j = i;
		i++;
	}
	return (dist);
}
