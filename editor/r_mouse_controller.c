#include "../includes/editor.h"

void		handle_left_click(t_ed *ed) {
	if (corner_selected(ed)){
		ft_putendl("vertex selected");
	} else if (sector_selected(ed)){
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
