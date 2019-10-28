
#include "../includes/doom_nukem.h"
int t;
int		load_sound2(t_data *d, int f)
{
	static int	i;
	uint8_t		*tmp_file;
	int			size_of_file;
	SDL_RWops	*rw;

	if ((t += read(f, &size_of_file, sizeof(int))) < 0)
		return (printf("Failed to read size of sound_file\n"));
	if (!(tmp_file = malloc(size_of_file)))
		return (printf("Failed to malloc sound\n"));
	if ((t += read(f, tmp_file, size_of_file)) < 0)
		return (printf("Failed to read sound file\n"));
	if (!(rw = SDL_RWFromMem(tmp_file, size_of_file)))
		return (printf("failed to init rw: %s\n", SDL_GetError()));
	if (!(d->chunk[i] = Mix_LoadWAV_RW(rw, 1)))
		return (printf("Failed to initialize chunk with Mix\n"));
	free(tmp_file);
	i++;
	return (0);
}

int		load_sound(t_data *d, int f)
{
	short	i;
t = 0;
	i = 0;
	if (d->chunk[0])
		return (0);
	while (i++ < NB_OF_SOUNDS)
		if (load_sound2(d, f))
			return (1);
	printf("total sound read: %d\n", t);
	return (0);
}
