#include "../includes/editor.h"


static void	do_select(t_ed *e, int inc)
{
	e->selection.select += inc;
	if (e->selection.select < 2)
		e->selection.select = 11;
	if (e->selection.select > 11)
		e->selection.select = 2;
}

static void	affect(t_ed *e, int inc)
{

}


void		listen_controls(bool *end, t_ed *ed)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			*end = true;
		mouse_controller(ed, &event);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
				affect(ed, -1);
			if (event.key.keysym.sym == SDLK_RIGHT)
				affect(ed, 1);
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			    *end = true;
			if (event.key.keysym.sym == SDLK_UP)
				do_select(ed, -1);
			if (event.key.keysym.sym == SDLK_DOWN)
				do_select(ed, 1);
		}
		   
	}

}
