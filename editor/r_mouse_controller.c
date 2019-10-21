#include "../includes/editor.h"

void		handle_left_click(t_ed *ed)
{
	if (ed->selection.drawing)
		loop_creation(ed);
	else
		corner_selected(ed);
}

int 		intersects(t_v2 line[2], t_sect *s)
{

}

// возвращает номер сектора ели внутри него кликнули или -1
char		in_sector(t_ed *e)
{
	int 	i;
	t_v2	line[2];
	int 	j;

	i = -1;
	while (++i < e->n_sect && (j = -1))
	{
		line[1] = new_v2(
		(e->seclist[i].walls[0].v1.x + e->seclist[i].walls[0].v2.x) >> 1,
		(e->seclist[i].walls[0].v1.y + e->seclist[i].walls[0].v2.y) >> 1);
		line[0] = e->controller.mouse;
		if (intersects(line, &e->seclist[i]) & 1)
			return (i);
	}
	return (-1);
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
