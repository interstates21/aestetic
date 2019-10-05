#include "../includes/doom_nukem.h"


static void	redraw(t_data *d, int choice)
{
	static char buf[] = M;

	buf[0] = (choice == 0) ? '>' : ' ';
	buf[24] = (choice == 1) ? '>' : ' ';
	buf[46] = (choice == 2) ? '>' : ' ';
	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){buf, WIDTH / 2 - 150, HEIGHT / 2 - 80, 0xffffff,
			2});
	SDL_UpdateWindowSurface(d->win);
 }

void		difficulty_menu(t_data *d)
{
	SDL_Event	e;
	static int	choice = 1;

	redraw(d, choice);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		else if (e.key.keysym.sym == SDLK_UP)
			choice = ft_mod((choice - 1), NB_MENU_ITEMS);
		else if (e.key.keysym.sym == SDLK_DOWN)
			choice = ft_mod((choice + 1), NB_MENU_ITEMS);
		else if (e.key.keysym.sym == SDLK_RETURN)
		{
			d->difficulty = choice;
			intro_screen(d);
		}
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			return ;
		redraw(d, choice);
	}
 }
