#include "../includes/doom_nukem.h"

void	set_doorstate(t_data *d)
{
	short	i;

	i = 0;
	while (i < d->numwalls)
	{
		d->dooranimstep[i] = 0.0;
		d->doorstate[i] = 0.0;
		i++;
	}
}

void	init_everything(t_data *d, char *map)
{
	int i;
	int	j;
	int	k;

	i = -1;
	while (++i < MAXTYPEMONSTERS && (j = -1))
		while (++j < MAX_STATE_MONSTER && (k = -1))
			while (++k < MAXNBOFANIMATION)
				d->monster_text[i][j][k] = NULL;
	load_map(d, map);
	set_doorstate(d);
	fix_picnum(d);
	init_player(d, &d->player);
	init_monsters(d);
	init_projectiles(d);
	if (d->startsectnum < 0)
		print_err("error");
	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
	{
		print_err("error");
	}
	d->floorheightplayer = get_floorheight_player(d, d->cursectnum);
	d->ceilheightplayer = get_ceilheight_player(d, d->cursectnum);
	play_music(d, MAIN_MUSIC);
	next_sect_fix(d);
	loop(d);
}

void	run(char *mapname)
{
	t_data d;
	SDL_Event e;
	int z;

	z = 0;
	init_font(&d);
	d.loaded = 0;
	init_sdl(&(d.sdl));
	TTF_Init();
	d.gFont = TTF_OpenFont("/Library/Fonts/Arial.ttf", 25);
	init_keys(&(d.keys));
	while (z == 0)
			z = draw_background(&d, e);
	d.zbuffer = get_screen_pixels();
	ft_strncpy(d.nextmap, mapname, 100);
	init_everything(&d, d.nextmap);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		print_err("Wrong number of args =(");
	if (!validate_argv(argv[1]))
		print_err("Wrong mapname");
	run(argv[1]);
}
