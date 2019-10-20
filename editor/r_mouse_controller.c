#include "../includes/editor.h"

// bool		sector_selected(t_ed *ed) {
// 	if (!ed)
// 		return (false);
// 	return (true);
// }
void		store_selected(t_ed *ed, t_wall *w, t_v2 *v) {
	ed->selection.selected_vertex = v;
	ed->selection.selected_wall = w;
	ft_putendl("selected");
}

bool		correct_vertex_selected(t_ed *ed) {
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

void		handle_left_click(t_ed *ed) {
	if (correct_vertex_selected(ed)){
		ft_putendl("vertex selected");
	}
}

int			mouse_controller(t_ed *ed, SDL_Event *event)
{
	SDL_GetMouseState(&(ed->controller.mouse.x), &(ed->controller.mouse.y));
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		ed->controller.mouse_is_pressed = true;
		if (event->button.button == SDL_BUTTON_LEFT) {
			handle_left_click(ed);
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
			ft_putendl("right pressed");
	}
	else if (event->type == SDL_MOUSEBUTTONUP) {
		ed->controller.mouse_is_pressed = false;
		// handle_mouse_off();
	}
	return (0);
}
