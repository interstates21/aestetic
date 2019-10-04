#include "../includes/doom_nukem.h"

void	proper_exit(t_data *d)
{
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	err_exit(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
