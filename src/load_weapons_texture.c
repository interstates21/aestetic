#include "../includes/doom_nukem.h"

int		load_weapons_texture(t_data *d, int f, int *nb_tex,
													int *nb_projectiles)
{
	int			i;
	int			j;
	int			w;
	int			h;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < nb_tex[i])
			if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0 ||
				!(d->weapon_tex[i][j] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)) ||
				read(f, d->weapon_tex[i][j]->pixels, w * h * 4) < 0)
				return (printf("Failed to read texture weapon.\n"));
		j = -1;
		while (++j < nb_projectiles[i])
			if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0 ||
				!(d->projectile_tex[i][j] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)) ||
				read(f, d->projectile_tex[i][j]->pixels, w * h * 4) < 0)
				return (printf("Failed to read texture projectile.\n"));
	}
	return (0);
}
