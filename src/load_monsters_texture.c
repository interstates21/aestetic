
#include "../includes/doom_nukem.h"

static void	read_motherdemon_projectile(t_data *d, int f)
{
	int		i;
	int		w;
	int		h;

	i = 0;
	while (i < 5)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0 ||
			!(d->projectile_tex[1][i] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)) ||
			read(f, d->projectile_tex[1][i]->pixels, w * h * 4) < 0)
				print_err("Failed load proj demon");
		i++;
	}
}

static void	read_anim_death_texture(t_data *d, int f, int *i, int nb_o)
{
	int	o;
	int	w;
	int	h;

	if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
		print_err("failed read death 1");
	if (!(d->monster_text[i[0]][i[1]][0] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
		print_err("failed read death 2");
	if (read(f, d->monster_text[i[0]][i[1]][0]->pixels, w * h * 4) < 0)
		print_err("failed read death 3");
	o = 0;
	while (++o < nb_o)
		d->monster_text[i[0]][i[1]][o] = d->monster_text[i[0]][i[1]][0];
}

static void	read_anim_texture(t_data *d, int f, int *i, int nb_o)
{
	int	o;
	int	w;
	int	h;

	o = -1;
	while (++o < nb_o)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Failed load proj");
		if (!(d->monster_text[i[0]][i[1]][o] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Failed load proj");
		if (read(f, d->monster_text[i[0]][i[1]][o]->pixels, w * h * 4) < 0)
			print_err("Failed load proj");
	}
}

void			load_monsters_texture(t_data *d, int f)
{
	int i;
	int a;
	int nb_orientation;
	int	nb_death;

	i = 0;
	while (i < 2)
	{
		a = -1;
		if (read(f, &nb_orientation, sizeof(int)) < 0)
			print_err("cannot read num orientation monsters");
		while (++a < 7)
			read_anim_texture(d, f, (int[2]){i, a}, nb_orientation);
		if (read(f, &nb_death, sizeof(int)) < 0)
			print_err("cannot read num death");
		a = 18 - nb_death;
		while (++a < 19)
			read_anim_death_texture(d, f, (int[2]){i, a}, nb_orientation);
		i++;
	}
	read_motherdemon_projectile(d, f);
}
