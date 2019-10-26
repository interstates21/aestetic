#include "../includes/editor.h"

static void	realloc_walls(t_ed *e)
{
	t_wall	*tmp;
	int 	i;

	tmp = (t_wall*)malloc(sizeof(t_wall) * (e->n_walls + 1));
	i = -1;
	while (++i < e->n_walls)
	{
		tmp[i] = e->walls[i];
	}
	free(e->walls);
	e->walls = tmp;
	e->n_walls += 1;
}

static void	realloc_sectors(t_ed *e)
{
	t_sect	*tmp;
	int 	i;

	tmp = (t_sect*)malloc(sizeof(t_sect) * (e->n_sect + 1));
	i = -1;
	while (++i < e->n_sect)
	{
		tmp[i] = e->seclist[i];
	}
	free(e->seclist);
	e->seclist = tmp;
	e->n_sect += 1;
}

static void	append_all_walls(t_ed *e)
{
	t_wall	*tmp;
	int 	i;
	int 	j;

	tmp = (t_wall*)malloc(sizeof(t_wall) * (e->n_all_w + e->n_walls));
	i = -1;
	while (++i < e->n_all_w)
		tmp[i] = e->all_walls[i];
	j = -1;
	while (++j < e->n_walls)
		tmp[i + j] = e->walls[j];
	// if (e->all_walls)
	// 	free(e->all_walls); leaks
	e->n_all_w = e->n_walls;
	e->all_walls = tmp;
}

void		finish_sector(t_ed *e, int sn)
{
	realloc_sectors(e);
	e->seclist[e->n_sect - 1] = init_sector(&e->walls, e->n_walls, e->n_sect - 1);
	e->selection.selected_wall->is_portal = e->n_sect - 1;
	e->seclist[e->n_sect - 1].walls[e->seclist[e->n_sect - 1].n_walls
	- 1].is_portal = sn;
	e->seclist[e->n_sect - 1].start_wall = e->n_all_w - 1;
	e->selection = (t_selection){.selected_wall = NULL, .selected_vertex = NULL};
	append_all_walls(e);
	e->walls = NULL;
	e->n_walls = 0;
}

void		wall_push(t_ed *e, t_v2 v1, t_v2 v2)
{
	realloc_walls(e);
	e->walls[e->n_walls - 1] = (t_wall){.is_door = 0, .is_portal = -1,
	.v1 = v1, .v2 = v2};
}