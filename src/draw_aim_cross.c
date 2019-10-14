#include "../includes/doom_nukem.h"

void	load_weapons_texture(t_data *d, int f, int *nb_tex,
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
				print_err("cannot read num weapon");
		j = -1;
		while (++j < nb_projectiles[i])
			if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0 ||
				!(d->projectile_tex[i][j] = SDL_CreateRGBSurfaceWithFormat(
						0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)) ||
				read(f, d->projectile_tex[i][j]->pixels, w * h * 4) < 0)
				print_err("cannot read texture projectile");
	}
}

void	draw_aim_cross(t_data *d)
{
	short		i;
	uint32_t	colo;
	if (d->player.current_weapon == CRYO_BALLISTA)
		colo = 0xDDFF;
	i = -1;
	while (++i < 10)
		putpixel(d, (WIDTH >> 1) - 16 + i, HEIGHT >> 1, colo);
	i += 12;
	while (++i < 32)
		putpixel(d, (WIDTH >> 1) - 16 + i, HEIGHT >> 1, colo);
	i = -1;
	while (++i < 10)
		putpixel(d, WIDTH >> 1, (HEIGHT >> 1) - 16 + i, colo);
	i += 12;
	while (++i < 32)
		putpixel(d, WIDTH >> 1, (HEIGHT >> 1) - 16 + i, colo);
	putpixel(d, WIDTH >> 1, HEIGHT >> 1, colo);
}
