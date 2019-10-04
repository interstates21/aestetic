
#include "editor.h"

static int		load_interface_assets(t_data *d, t_toolbar *tb)
{
	int		m;
	int		j;
	int		i;
	char	*file;

	m = 0;
	i = 0;
	while (m < NB_CATEGORY - 1)
	{
		j = -1;
		while (++j < d->interface.nb_asset[m])
		{
			file = d->assets_data[i].file;
			if (!(tb->assets[m][j] = load_bmp(file)))
				return (printf("Loading failed : %s\n", file));
			i++;
		}
		m++;
	}
	if (!(tb->player_start = load_bmp(d->assets_data[i].file)))
		return (printf("Loading failed : %s\n", d->assets_data[i].file));
	return (0);
}

static int		init_assets(t_data *d, t_toolbar *tb)
{
	if (get_interface_assets_files(d, (char*[]){PATH_ASSETS, PATH_MONSTER_ED,
								PATH_PLAYERSTART_ED}))
		return (1);
	if (load_interface_assets(d, tb))
		return (1);
	if (!(d->texture_monster = (t_monsters_texture*)malloc(
		sizeof(t_monsters_texture) * d->interface.nb_asset[1])))
		return (printf("Failed to allocate texture_monster.\n"));
	if (get_monsters_files(d, PATH_MONSTERS, d->interface.nb_asset[1]))
		return (1);
	return (0);
}

static int		init_toolbar(t_toolbar *tb)
{
	char	**file;
	int		i;
	int		j;

	file = (char*[]){"./Menu/Select_disable.bmp", "./Menu/Select_enable.bmp",
	"./Menu/Move_disable.bmp", "./Menu/Move_enable.bmp",
	"./Menu/lblSector.bmp", "./Menu/lblsector_info.bmp", "./Menu/lblWall.bmp",
	"./Menu/lblTexture.bmp", "./Menu/lblAssets.bmp", "./Menu/lblMonsters.bmp",
	"./Menu/assetsOptions.bmp", "./Menu/lblPlayerStart.bmp",
	"./Menu/minus.bmp", "./Menu/plus.bmp", "./Menu/lblLight.bmp",
	"./Menu/lblSkybox.bmp", "./Menu/lblDoor.bmp", "./Menu/checkBoxEmpty.bmp",
	"./Menu/checkBox.bmp", "./Menu/lblPoster.bmp", "./Menu/lblEnd.bmp",
	"./Menu/lblNextmap.bmp", "./Menu/browseBox.bmp",
	"./Menu/sectorOptions.bmp", "./Menu/lblTransparent.bmp"};
	i = -1;
	if (!(tb->select[0] = load_bmp(file[++i])) ||
		!(tb->select[1] = load_bmp(file[++i])) ||
		!(tb->move[0] = load_bmp(file[++i])) ||
		!(tb->move[1] = load_bmp(file[++i])))
		return (printf("Failed to load %s\n", file[i]));
	j = -1;
	while (++j < NB_PROPERTIES)
		if (!(tb->properties[j] = load_bmp(file[++i])))
			return (printf("Failed to load %s\n", file[i]));
	return (0);
}

static int		init_interface(t_data *d)
{
	if (!(d->interface.menu = load_bmp("./Menu/menu.bmp")))
		return (printf("Error when creating escape menu.\n"));
	if (init_toolbar(&d->interface.toolbar) ||
		init_assets(d, &d->interface.toolbar))
		return (1);
	init_button_position(d, 0, 0, &d->interface.btn_option_p);
	return (0);
}

int				init_editor(t_data *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		return (printf("Failed to init SDL.\n"));
	if (!(d->win = SDL_CreateWindow("editor", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, W, H, 0)))
		return (printf("Failed to create editor's window.\n"));
	if (!(d->screen = SDL_GetWindowSurface(d->win)))
		return (printf("Failed to get window's surface.\n"));
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		return (printf("Failed to init audio Mixer\n"));
	if (init_interface(d) || init_texture(d))
		return (1);
	return (0);
}
