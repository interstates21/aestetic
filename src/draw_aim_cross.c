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


void	draw_blaster_aim(t_data *d)
{
	short i;

	i = (WIDTH * 0.5) - 10;
	while (--i > (WIDTH >> 1) - 22)
		putpixel(d, i, HEIGHT >> 1, GREEN_BLAST);
	i = (WIDTH * 0.5) + 10;
	while (++i < (WIDTH >> 1) + 22)
		putpixel(d, i, HEIGHT >> 1, GREEN_BLAST);
	putpixel(d, (WIDTH >> 1) + 1, HEIGHT >> 1, GREEN_BLAST);
	putpixel(d, (WIDTH >> 1) - 1, HEIGHT >> 1, GREEN_BLAST);
	putpixel(d, WIDTH >> 1, HEIGHT >> 1, GREEN_BLAST);
}

void	draw_aim_cross(t_data *d)
{
	short		i;
	uint32_t	colo;

	if (d->player.current_weapon == M16)
		colo = 0xFF0000;
	if (d->player.current_weapon == BLASTER)
	{
		draw_blaster_aim(d);
		return ;
	}
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
