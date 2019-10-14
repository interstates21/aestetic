
#include "../includes/doom_nukem.h"

void		read_posters_data(t_data *d, int f)
{
	int	i;
	int w;
	int h;
	size_t postersSize;

	if (read(f, &d->nb_posters, sizeof(int32_t)) < 0)
		print_err("Cannot read num posters");
	if (d->nb_posters <= 0)
		return ;
	postersSize = sizeof(SDL_Surface*) * d->nb_posters;
	d->posters = (SDL_Surface**)pureMalloc(postersSize, "Cannot alloc posters");
	i = -1;
	while (++i < d->nb_posters)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Cannot read posters size");
		if (!(d->posters[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Cannot allocate posters");
		if ((read(f, d->posters[i]->pixels, w * h * 4)) < 0)
			print_err("Cannot read poster data");
	}
}

void		read_monsters_data(t_data *d, int f)
{
	int	i;
	size_t monstersSize;

	if (read(f, &d->nummonsters, sizeof(uint16_t)) < 0)
		print_err("Cannot read num monsters");
	if (d->nummonsters > 0)
	{
		monstersSize = sizeof(t_monster) * d->nummonsters;
		d->monsters = (t_monster*)pureMalloc(monstersSize, "cannot alloc monsters");
		i = -1;
		while (++i < d->nummonsters)
			if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
			print_err("Cannot read monsters data");
	}
}

void		read_assets_texture(t_data *d, int f)
{
	int	i;
	int	w;
	int	h;
	size_t assetsSize;

	if (read(f, &d->nb_assets_texture, sizeof(int16_t)) < 0)
		print_err("Cannot read num assets");
	if (d->nb_assets_texture <= 0)
		return ;
	assetsSize = sizeof(SDL_Surface*) * d->nb_assets_texture;
	d->assets_texture = (SDL_Surface**)pureMalloc(assetsSize, "cannot alloc assets");
	i = -1;
	while (++i < d->nb_assets_texture)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Cannot read asset size");
		if (!(d->assets_texture[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Cannot alloc assets");
		if ((read(f, d->assets_texture[i]->pixels, w * h * 4)) < 0)
			print_err("Cannot read asset texture");
	}
}


void		read_assets_data(t_data *d, int f)
{
	int	i;
	int	s;
	size_t assetsSize;
	size_t subAssetsSize;

	if (read(f, &d->nb_assets, sizeof(int16_t)) < 0)
		print_err("Cannot read assets num");
	assetsSize = sizeof(t_assets*) * d->numsectors;
	d->assets = (t_assets**)pureMalloc(assetsSize, "cannot alloc assets");
	if (d->nb_assets > 0)
	{
		s = -1;
		while (++s < d->numsectors)
		{
			subAssetsSize = sizeof(t_assets) * 10;
			d->assets[s] = (t_assets*)pureMalloc(subAssetsSize, "cannot alloc subAssets");
			if (read(f, &d->assets[s][0].nb_assets, sizeof(int)) < 0)
				print_err("Cannot read nb asset for sect");
			i = -1;
			while (++i < d->assets[s][0].nb_assets)
				if (read(f, &d->assets[s][i], sizeof(t_assets)) < 0)
					print_err("Cannot read asset[][]");
		}
	}
}
