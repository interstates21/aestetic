#include "../includes/doom_nukem.h"

void	precompute_texanim(t_data *d)
{
	int			i;
	SDL_Surface	*s;
	int			framenum;
	int			numframes;

	framenum = SDL_GetTicks() / 80;
	i = -1;
	while (++i < d->nb_textures)
	{
		s = d->textures[i];
		if ((numframes = (s->h / s->w)) > 5)
			s->userdata = (void*)(intptr_t)(framenum % numframes + 1);
		else
			s->userdata = 0;
	}
}
