#include "editor.h"

void	fix_outside_monster_and_assets(t_data *d, t_monster_list *mlst,
													t_assets_list *alst)
{
	t_monster_list	*mnext;
	t_assets_list	*anext;

	mlst = d->interface.monster_list ? d->interface.monster_list->begin : NULL;
	alst = d->interface.assets_list ? d->interface.assets_list->begin : NULL;
	while (mlst)
	{
		mnext = mlst->next;
		if (!inside(d, mlst->sectnunm, mlst->pos))
		{
			mlst->is_select = 1;
			delete_monster(d, d->interface.monster_list);
		}
		mlst = mnext;
	}
	while (alst)
	{
		anext = alst->next;
		if (!inside(d, alst->sectnunm, alst->world_pos))
		{
			alst->is_select = 1;
			delete_asset(d, d->interface.assets_list, NULL, NULL);
		}
		alst = anext;
	}
}

void	draw_selection_arround_selected_asset(t_data *d, t_vec2 *v, int c)
{
	int		x;
	int		y;

	x = d->mouse.x;
	y = d->mouse.y;
	x = -1;
	while (++x < 32)
		putpixel(d, x + v->x, v->y, c);
	x = -1;
	while (++x < 32)
		putpixel(d, x + v->x, v->y + 32, c);
	y = -1;
	while (++y < 32)
		putpixel(d, v->x, y + v->y, c);
	y = -1;
	while (++y < 32)
		putpixel(d, v->x + 32, y + v->y, c);
}

void	draw_selection_arround_asset(t_data *d, t_vec2 *category_pos)
{
	int		x;
	int		y;
	t_vec2	v;

	v = d->mouse;
	if (v.x + 1 + v.y * NB_ASSET_LINE >
							d->interface.nb_asset[d->interface.category])
		return ;
	v.x = (v.x * 38) + category_pos[d->interface.category].x;
	v.y = (v.y * 36) + category_pos[d->interface.category].y;
	x = -1;
	while (++x < 32)
		putpixel(d, x + v.x, v.y, 0xffff00);
	x = -1;
	while (++x < 32)
		putpixel(d, x + v.x, v.y + 32, 0xffff00);
	y = -1;
	while (++y < 32)
		putpixel(d, v.x, y + v.y, 0xffff00);
	y = -1;
	while (++y < 32)
		putpixel(d, v.x + 32, y + v.y, 0xffff00);
	show_preview(d, d->interface.toolbar.assets);
}

void	get_selected_asset(t_data *d)
{
	int		x;
	int		y;

	x = d->mouse.x;
	y = d->mouse.y;
	if (x + 1 + y * NB_ASSET_LINE >
								d->interface.nb_asset[d->interface.category])
		return ;
	d->interface.selected_asset = x + y * NB_ASSET_LINE;
	d->interface.select = 0;
	x = x * 38 + d->interface.category_pos[d->interface.category].x;
	y = y * 36 + d->interface.category_pos[d->interface.category].y;
	d->interface.selected_asset_position = (t_vec2){x, y};
	d->interface.selected_asset_cat = d->interface.category;
}

/*
**	4 category (0 to 3)
*/

int		add_asset_to_map(t_data *d, int x, int y)
{
	int			sectornum;
	t_sector	*s;
	t_vec2f		p;

	if ((sectornum = find_sect_under_cursor(d)) < 0)
		return (printf("Assets must be place inside a sector\n"));
	s = &d->sectors[sectornum];
	p = screentoworld(d, (t_vec2f){x, y});
	if (d->interface.selected_asset_cat == 2)
	{
		d->player_start = (t_vec3f){p.x, s->floorheight + 0.5, p.y};
		d->startsectnum = sectornum;
	}
	else if (d->interface.selected_asset_cat == 1)
		add_monster_to_list(d, &p, sectornum, &d->interface);
	else if (d->interface.selected_asset_cat == 0)
		add_assets_to_list(d, &p, sectornum, &d->interface);
	d->interface.selected_asset_cat = -1;
	d->interface.selected_asset = -1;
	d->interface.select = 1;
	return (0);
}
