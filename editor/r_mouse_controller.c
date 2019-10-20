#include "../includes/editor.h"

int			mouse_controller(t_ed *ed, SDL_Event *event)
{
	SDL_GetMouseState(&(ed->controller.mouse.x), &(ed->controller.mouse.y));
	// if (event->type == SDL_MOUSEBUTTONDOWN)
        	
	// else if (event->type == SDL_MOUSEBUTTONUP)

	return (0);
}
