
#include "../includes/doom_nukem.h"

void		read_posters_data(t_data *d, int f)
{
	int	i;
	int w;
	int h;

	if (read(f, &d->nb_posters, sizeof(int32_t)) < 0)
		print_err("Cannot read num posters");
	printf("poser = %d\n", d->nb_posters);
	if (d->nb_posters <= 0)
		return ;
	if (!(d->posters =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_posters)))
		print_err("Cannot allocate posters");
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
	int t = 0;

	if ((t += read(f, &d->nummonsters, sizeof(uint16_t))) < 0)
		print_err("Cannot read num monsters");
	if (d->nummonsters > 0)
	{
		if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) *
														d->nummonsters)))
			print_err("Cannot allocate monster struct");
		i = -1;
		while (++i < d->nummonsters)
			if ((t += read(f, &d->monsters[i], sizeof(t_monster))) < 0)
			print_err("Cannot read monsters data");
	}
}

void		read_assets_texture(t_data *d, int f)
{
	int	i;
	int	w;
	int	h;
int t = 0;
	if ((t += read(f, &d->nb_assets_texture, sizeof(int16_t))) < 0)
		print_err("Cannot read num assets");
	if (d->nb_assets_texture <= 0)
		return ;
	if (!(d->assets_texture =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_assets_texture)))
		print_err("Cannot allocate asset texture");
	i = -1;
	while (++i < d->nb_assets_texture)
	{
		if ((t += read(f, &w, sizeof(int))) < 0 || (t += read(f, &h, sizeof(int))) < 0)
			print_err("Cannot read asset size");
		if (!(d->assets_texture[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Cannot alloc assets");
		if (((t += read(f, d->assets_texture[i]->pixels, w * h * 4))) < 0)
			print_err("Cannot read asset texture");
	}
	printf("sprite_tex total read: %d\n", t);
}


void		read_assets_data(t_data *d, int f)
{
	int	i;
	int	s;
	int t = 0;

	if ((t += read(f, &d->nb_assets, sizeof(int16_t))) < 0)
		print_err("Cannot read assets num");
	printf("n_asset = %d\n", d->nb_assets);
	if (!(d->assets = (t_assets**)malloc(sizeof(t_assets*) * d->numsectors)))
		print_err("Cannot alloc asset data");
	if (d->nb_assets > 0)
	{
		s = -1;
		while (++s < d->numsectors)
		{
			if (!(d->assets[s] = (t_assets*)malloc(sizeof(t_assets) * 10)))
				print_err("Cannot alloc asset struct");
			if ((t += read(f, &d->assets[s][0].nb_assets, sizeof(int))) < 0)
				print_err("Cannot read nb asset for sect");
			i = -1;
			while (++i < d->assets[s][0].nb_assets)
				if ((t += read(f, &d->assets[s][i], sizeof(t_assets))) < 0)
					print_err("Cannot read asset[][]");
		}
	}
	printf("total read: %d\n", t);
}
