
#include "../includes/doom_nukem.h"

void		load_sound(t_data *d, int f)
{
	int			i;
	int			size;
	uint8_t		*buff;
	SDL_RWops	*r_wops;

	i = 0;
	if (d->chunk[0])
		return ;
	while (i++ < NB_OF_SOUNDS)
	{
		if (read(f, &size, sizeof(int)) < 0)
			print_err("cannot read sound data");
		buff = pure_malloc(size, "cannot alloc sound");
		if (read(f, buff, size) < 0)
			print_err("cannot read sound data");
		if (!(r_wops = SDL_RWFromMem(buff, size)))
			print_err("cannot init sdl sound");
		if (!(d->chunk[i] = Mix_LoadWAV_RW(r_wops, 1)))
			print_err("cannot init sdl sound chank");
		free(buff);
	}
}
