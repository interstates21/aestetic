/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_toggle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 15:41:42 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/14 18:55:27 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	remove_key(t_data *d, t_wall *w)
{
	t_assets_list *lst;

	if (!d->interface.assets_list)
		return ;
	lst = d->interface.assets_list->begin;
	while (lst)
	{
		if (lst->is_key && lst->key_num == w->key_num)
		{
			lst->is_key = !lst->is_key;
			lst->key_num = 0;
		}
		lst = lst->next;
	}
}

t_wall		*get_adjacent_wall(t_data *d, t_wall *w)
{
	t_sector	*sect;
	int16_t		wallnum;
	int16_t		nextwallnum;

	sect = &d->sectors[in_which_sector_is_this_wall(d, w)];
	wallnum = w - d->walls;
	nextwallnum = ((wallnum - sect->firstwallnum + 1) % sect->numwalls)
													+ sect->firstwallnum;
	return (&d->walls[nextwallnum]);
}

/*
**	get the portal from the neighbor sector and set it as a door too.
*/

void		find_opposite_portal(t_data *d, t_sector *neighborsect,
									int16_t *last, t_wall *nextwall)
{
	int		i;
	int		j;

	i = *last - 1;
	j = neighborsect->firstwallnum;
	while (j < *last)
	{
		if (d->walls[i].neighborsect != -1 &&
			same_pos(&d->walls[i], nextwall) &&
			same_pos(&d->walls[j], d->selectedwall))
		{
			d->walls[i].is_door = d->selectedwall->is_door;
			d->walls[i].door_num = d->selectedwall->door_num;
			break ;
		}
		i = j++;
	}
}

void		toggle_isdoor(t_data *d, int16_t last)
{
	t_sector	*neighborsect;
	t_wall		*nextwall;

	if (d->selected_wall != -1 || d->hl_wallnum != -1)
	{
		d->selectedwall = d->walls +
				((d->selected_wall != -1) ? d->selected_wall : d->hl_wallnum);
		if (d->selectedwall->neighborsect == -1)
		{
			printf("Only portals can be doors !\n");
			d->selectedwall = NULL;
			return ;
		}
		d->nb_door += (!d->selectedwall->is_door) ? 1 : 0;
		d->selectedwall->door_num = (!d->selectedwall->is_door) ?
									d->nb_door : -1;
		if (d->selectedwall->is_door)
			remove_key(d, d->selectedwall);
		d->selectedwall->is_door = !d->selectedwall->is_door;
		neighborsect = d->sectors + d->selectedwall->neighborsect;
		nextwall = get_adjacent_wall(d, d->selectedwall);
		last = neighborsect->firstwallnum + neighborsect->numwalls;
		find_opposite_portal(d, neighborsect, &last, nextwall);
	}
	d->selectedwall = NULL;
}
