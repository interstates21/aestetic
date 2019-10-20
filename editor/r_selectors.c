#include "../includes/editor.h"

void		store_selected(t_ed *ed, t_wall *w, t_v2 *v) {
	ed->selection.selected_vertex = v;
	ed->selection.selected_wall = w;
}

// bool		inside(t_data *d, int16_t sectnum, t_vec2f p)
// {
// 	int		i;
// 	int		j;
// 	bool	c;
// 	t_vec2f	w0;
// 	t_vec2f	w1;

// 	c = 0;
// 	i = 0;
// 	j = d->sectors[sectnum].numwalls - 1;
// 	while (i < d->sectors[sectnum].numwalls)
// 	{
// 		w0 = d->walls[d->sectors[sectnum].firstwallnum + i].point;
// 		w1 = d->walls[d->sectors[sectnum].firstwallnum + j].point;
// 		if (((w0.y > p.y) != (w1.y > p.y)) &&
// 			(p.x < (w1.x - w0.x) * (p.y - w0.y) / (w1.y - w0.y) + w0.x))
// 			c = !c;
// 		j = i++;
// 	}
// 	return (c);
// }

// int16_t		find_sect_under_cursor(t_data *d)
// {
// 	int		x;
// 	int		y;
// 	int		s;
// 	t_vec2f	p;

// 	SDL_GetMouseState(&x, &y);
// 	p = screentoworld(d, (t_vec2f){x, y});
// 	s = -1;
// 	while (++s < d->numsectors)
// 		if (inside(d, s, p))
// 			return (s);
// 	return (-1);
// }


bool		sector_selected(t_ed *ed) {
	int i;

	i = 0;
	while (i < 4) {
		if (v2_compare(ed->initial_walls[i].v1, ed->controller.mouse, SELECTION_FIELD)) {
			store_selected(ed, &(ed->initial_walls[i]), &(ed->initial_walls[i].v1));
			return (true);
		}
		else if (v2_compare(ed->initial_walls[i].v2, ed->controller.mouse, SELECTION_FIELD)) {
			store_selected(ed, &(ed->initial_walls[i]), &(ed->initial_walls[i].v2));
		}
		i++;
	}
	return (false);
}

bool		corner_selected(t_ed *ed) {
	int i;

	i = 0;
	while (i < 4) {
		if (v2_compare(ed->initial_walls[i].v1, ed->controller.mouse, SELECTION_FIELD)) {
			store_selected(ed, &(ed->initial_walls[i]), &(ed->initial_walls[i].v1));
			return (true);
		}
		else if (v2_compare(ed->initial_walls[i].v2, ed->controller.mouse, SELECTION_FIELD)) {
			store_selected(ed, &(ed->initial_walls[i]), &(ed->initial_walls[i].v2));
		}
		i++;
	}
	return (false);
}
