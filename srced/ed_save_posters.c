
#include "editor.h"

int		write_posters_data(t_data *d, int f)
{
	int				i;

	if (write(f, &d->nb_posters, sizeof(int32_t)) < 0)
		return (printf("Error write nb posters.\n"));
	i = -1;
	while (++i < d->nb_posters)
	{
		if (write(f, &d->posters[i]->w, sizeof(int)) < 0 ||
			write(f, &d->posters[i]->h, sizeof(int)) < 0 ||
			write(f, d->posters[i]->pixels, 4 * (d->posters[i]->w *
												d->posters[i]->h)) < 0)
			return (printf("Failed to write texture data.\n"));
	}
	return (0);
}
