#include "../includes/editor.h"

void		handle_left_click(t_ed *ed)
{
	t_wall	tmp;

	if (corner_selected(ed))
		ft_putendl("vertex selected");

		if (!ed->selection.selected_wall)
			return;
		tmp = new_wall(ed->selection.val.x, ed->selection.val.y,
		ed->controller.mouse.x, ed->controller.mouse.y);
		wall_push(ed, tmp.v1, tmp.v2);
		ed->selection.val = ed->controller.mouse;
}

int			mouse_controller(t_ed *ed, SDL_Event *event)
{
	SDL_GetMouseState(&(ed->controller.mouse.x), &(ed->controller.mouse.y));
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		ed->controller.mouse_is_pressed = true;
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			handle_left_click(ed);
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
			ft_putendl("right pressed");
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		ed->controller.mouse_is_pressed = false;
		// handle_mouse_off();
	}
	return (0);
}
