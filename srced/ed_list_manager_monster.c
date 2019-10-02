/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_list_manager_monster.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:31:37 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/09 13:31:38 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		fix_list(t_data *d, t_monster_list *prev, t_monster_list *next)
{
	t_monster_list	*lst;

	if (prev)
		lst = prev;
	else
		lst = next;
	while (lst->prev)
		lst = lst->prev;
	lst->begin = lst;
	while (lst->next)
	{
		lst = lst->next;
		lst->begin = lst->prev->begin;
	}
	d->interface.monster_list = lst;
}

int				delete_monster(t_data *d, t_monster_list *lst)
{
	t_monster_list	*prev;
	t_monster_list	*next;

	while (lst)
	{
		if (lst->is_select)
		{
			prev = lst->prev;
			next = lst->next;
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			free(lst);
			if (!prev && !next)
				d->interface.monster_list = NULL;
			else
				fix_list(d, prev, next);
			d->nbmonsters--;
			d->interface.selected_monster_on_map = NULL;
			return (1);
		}
		lst = lst->prev;
	}
	return (0);
}

t_monster_list	*new_monster(char *name, t_vec2f *p, int sectnum,
											t_monster_list *prev)
{
	t_monster_list	*monster;

	if (!(monster = (t_monster_list*)malloc(sizeof(t_monster_list))))
		return (NULL);
	monster->name = name;
	monster->pos = *p;
	monster->sectnunm = sectnum;
	monster->category = -1;
	monster->selected_asset = -1;
	monster->is_highlighted = 0;
	monster->is_select = 0;
	monster->prev = prev;
	monster->next = NULL;
	return (monster);
}

int				add_monster_to_list(t_data *d, t_vec2f *p, int sectn,
															t_interface *i)
{
	int			selected_asset;
	char		*name;

	selected_asset = i->selected_asset;
	name = d->assets_data[i->nb_asset[0] + selected_asset].name;
	if (!d->interface.monster_list)
	{
		if (!(i->monster_list = new_monster(name, p, sectn, NULL)))
			return (printf("Failed to add monster.\n"));
		i->monster_list->begin = i->monster_list;
		i->monster_list->category = i->selected_asset_cat;
		i->monster_list->selected_asset = selected_asset;
	}
	else
	{
		if (!(i->monster_list->next = new_monster(name, p, sectn,
														i->monster_list)))
			return (printf("Failed to add next monster.\n"));
		i->monster_list->next->begin = i->monster_list->begin;
		i->monster_list->next->category = i->selected_asset_cat;
		i->monster_list->next->selected_asset = selected_asset;
		i->monster_list = i->monster_list->next;
	}
	d->nbmonsters++;
	return (0);
}
