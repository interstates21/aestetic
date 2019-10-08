#include "../includes/doom_nukem.h"

static void	redraw(t_data *d, int choice)
{
	static char buf[] = "  HELP\n  EXIT";

	buf[0] = (choice == 0) ? '>' : ' ';
	buf[7] = (choice == 1) ? '>' : ' ';
	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){buf, WIDTH / 2 - 50, HEIGHT / 2 - 60, 0xffffff,
			2});
	SDL_UpdateWindowSurface(d->win);
}

void		pause_menu(t_data *d)
{
	SDL_Event	e;
	static int	choice;

	if (SDL_SetRelativeMouseMode(SDL_FALSE) == -1)
		printf("SDL_SetRelativeMouseMode error");
	redraw(d, choice);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			proper_exit(d);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		if (e.key.keysym.sym == SDLK_UP)
			choice = MOD((choice - 1), 2);
		if (e.key.keysym.sym == SDLK_DOWN)
			choice = MOD((choice + 1), 2);
		if (e.key.keysym.sym == SDLK_RETURN && choice == 0)
			help_screen(d);
		if (e.key.keysym.sym == SDLK_RETURN && choice == 1)
			proper_exit(d);
		if (e.key.keysym.sym == SDLK_ESCAPE)
			return ((void)SDL_SetRelativeMouseMode(SDL_TRUE));
		redraw(d, choice);
	}
}
