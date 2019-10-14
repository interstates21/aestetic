#include "../includes/doom_nukem.h"

void	fix_picnum(t_data *d)
{
	int		i;
	int		name_i;

	i = -1;
	while (++i < d->numwalls && (name_i = -1))
		while (++name_i < d->nb_textures)
			if (ft_strequ(d->walls[i].texture_name, d->tex_name_list[name_i]))
			{
				d->walls[i].lowerpicnum = name_i;
				d->walls[i].middlepicnum = name_i;
				d->walls[i].upperpicnum = name_i;
			}
	i = -1;
	while (++i < d->numsectors && (name_i = -1))
		while (++name_i < d->nb_textures)
		{
			if (ft_strequ(d->sectors[i].floor_texture_name,
						  d->tex_name_list[name_i]))
				d->sectors[i].floorpicnum = name_i;
			if (ft_strequ(d->sectors[i].ceil_texture_name,
						  d->tex_name_list[name_i]))
				d->sectors[i].ceilpicnum = name_i;
		}
}

static void	init_ttf(t_sdl *sdl)
{
	if (TTF_Init() == -1)
		print_err(SDL_GetError());
}

void	init_sdl(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(sdl->win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0)))
		print_err(SDL_GetError());
	if (!(sdl->screen = SDL_GetWindowSurface(sdl->win)))
		print_err(SDL_GetError());
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)
	== -1)
		print_err(SDL_GetError());
	if (!Mix_AllocateChannels(MAX_CHANNELS))
		print_err(SDL_GetError());
	//init_ttf(sdl);
}

void	initKeys(Uint8 **keys) {
		*(keys) = (Uint8*)SDL_GetKeyboardState(NULL);
}