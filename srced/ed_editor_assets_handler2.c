#include "editor.h"

void		disable_asset_selection(t_data *d)
{
	if (d->interface.current_selected_asset)
	{
		d->interface.current_selected_asset->is_select = 0;
		d->interface.current_selected_asset = NULL;
		d->interface.prompt_asset_option = 0;
	}
	if (d->interface.selected_monster_on_map)
	{
		d->interface.selected_monster_on_map->is_select = 0;
		d->interface.selected_monster_on_map = NULL;
	}
	if (d->interface.selected_asset_on_map)
	{
		d->interface.selected_asset_on_map->is_select = 0;
		d->interface.selected_asset_on_map = NULL;
	}
}

void		move_asset(t_data *d, int x, int y)
{
	t_vec2f	p;

	p = screentoworld(d, (t_vec2f){x, y});
	if (inside(d, find_sect_under_cursor(d), p))
	{
		if (d->interface.selected_asset_on_map && d->interface.move)
			d->interface.selected_asset_on_map->world_pos = p;
		else if (d->interface.selected_monster_on_map && d->interface.move)
			d->interface.selected_monster_on_map->pos = p;
	}
	else
		printf("Asset must be place inside a sector.\n");
}

void		check_if_assets_inside_sector(t_data *d)
{
	t_monster_list	*ml;
	t_monster_list	*mtmp;
	t_assets_list	*al;
	t_assets_list	*atmp;

	ml = (d->interface.monster_list) ? d->interface.monster_list->begin : NULL;
	al = (d->interface.assets_list) ? d->interface.assets_list->begin : NULL;
	while (ml)
	{
		mtmp = ml->next;
		if (ml->sectnunm == d->selected_sector && (ml->is_select = 1))
			delete_monster(d, d->interface.monster_list);
		ml = mtmp;
	}
	while (al)
	{
		atmp = al->next;
		if (al->sectnunm == d->selected_sector && (al->is_select = 1))
			delete_asset(d, d->interface.assets_list, NULL, NULL);
		al = atmp;
	}
}

static int	select_monster_on_map(t_data *d)
{
	t_monster_list	*lst;
	int				found;

	found = 0;
	lst = d->interface.monster_list;
	while (lst)
	{
		lst->is_select = 0;
		if (lst->is_highlighted)
		{
			lst->is_select = 1;
			d->interface.selected_monster_on_map = lst;
			found = 1;
		}
		lst = lst->prev;
	}
	return (found);
}

int			select_assets_on_map(t_data *d)
{
	t_assets_list	*lst;
	int				found;

	if (select_monster_on_map(d))
		return (1);
	found = 0;
	lst = d->interface.assets_list;
	while (lst)
	{
		lst->is_select = 0;
		if (lst->is_highlighted)
		{
			lst->is_select = 1;
			d->interface.selected_asset_on_map = lst;
			found = 1;
		}
		lst = lst->prev;
	}
	return (found);
}
