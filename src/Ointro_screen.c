#include "../includes/doom_nukem.h"

/*
void	intro_screen(t_data *d)
{
	SDL_Event	e;

	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string_typewriter_effect(d, (t_font){
			"The world is invaded by demonic creatures.\n"
			"Your mission is to save Pikachu.\n"
			"Good luck !",
			WIDTH / 2 - 250, HEIGHT / 2 - 80, 0xffffff, 2});
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		else if (e.key.keysym.sym == SDLK_RETURN)
			init_everything(d, d->nextmap);
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			init_everything(d, d->nextmap);
	}
 }
*/
