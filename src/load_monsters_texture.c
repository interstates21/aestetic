
#include "../includes/doom_nukem.h"
int t;
static int	read_motherdemon_projectile(t_data *d, int f)
{
	int		i;
	int		w;
	int		h;

	i = -1;
	while (++i < 5)
	{
		if ((t += read(f, &w, sizeof(int))) < 0 || (t += read(f, &h, sizeof(int))) < 0 ||
			!(d->projectile_tex[1][i] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)) ||
				(t += read(f, d->projectile_tex[1][i]->pixels, w * h * 4)) < 0)
			return (printf("Failed to read motherdemon projectile\n"));
	}
	return (0);
}

static int	read_anim_death_texture(t_data *d, int f, int *i, int nb_o)
{
	int	o;
	int	w;
	int	h;

	if ((t += read(f, &w, sizeof(int))) < 0 || (t += read(f, &h, sizeof(int))) < 0)
		return (printf("Failed to read death texture size.\n"));
	if (!(d->monster_text[i[0]][i[1]][0] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
		return (printf("Failed to create monster death SDL_Surface.\n"));
	if ((t += read(f, d->monster_text[i[0]][i[1]][0]->pixels, w * h * 4)) < 0)
		return (printf("Failed to read monster texture.\n"));
	o = 0;
	while (++o < nb_o)
		d->monster_text[i[0]][i[1]][o] = d->monster_text[i[0]][i[1]][0];
	return (0);
}

static int	read_anim_texture(t_data *d, int f, int *i, int nb_o)
{
	int	o;
	int	w;
	int	h;

	o = -1;
	while (++o < nb_o)
	{
		if ((t += read(f, &w, sizeof(int))) < 0 || (t += read(f, &h, sizeof(int))) < 0)
			return (printf("Failed to read texture size.\n"));
		if (!(d->monster_text[i[0]][i[1]][o] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (printf("Failed to create monster anim SDL_Surface.\n"));
		if ((t += read(f, d->monster_text[i[0]][i[1]][o]->pixels, w * h * 4)) < 0)
			return (printf("Failed to read monster texture.\n"));
	}
	return (0);
}

void			load_monsters_texture(t_data *d, int f)
{
	int i;
	int a;
	int nb_orientation;
	int	nb_death;
t = 0;
	i = -1;
	while (++i < 2)
	{
		a = -1;
		if ((t += read(f, &nb_orientation, sizeof(int))) < 0)
			print_err("cannot read num orientation monsters");
		while (++a < 7)
			if (read_anim_texture(d, f, (int[2]){i, a}, nb_orientation))
				print_err("monst error");
		if ((t += read(f, &nb_death, sizeof(int))) < 0)
				print_err("cannot read num death");
		a = 18 - nb_death;
		while (++a < 19)
			if (read_anim_death_texture(d, f, (int[2]){i, a}, nb_orientation))
				print_err("cannot react anim death");
	}
	if (read_motherdemon_projectile(d, f))
			print_err("cannot read demon");
	printf("monster_tex total read: %d\n", t);
}
