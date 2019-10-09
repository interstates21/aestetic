#include "../includes/doom_nukem.h"

void	print_and_quit(t_data *d, const char *str)
{
	if (d->sdl.win)
		SDL_DestroyWindow(d->sdl.win);
	SDL_Quit();
	ft_putendl(ft_strjoin(("Good bye!"), str));
	exit(0);
}


void	print_err(const char *err)
{
	ft_putendl((ft_strjoin("Init Error = ", err)));
	exit(1);
}
