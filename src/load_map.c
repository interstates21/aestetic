
#include "../includes/doom_nukem.h"

static void	read_texture_data(t_data *d, int f)
{
	int	i;
	int w;
	int h;

	if (!(d->textures =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_textures)))
			print_err("cannot allocate texture memory");
	i = -1;
	while (++i < d->nb_textures)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Cannot read texture size");
		if (!(d->textures[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Cannot create texture surface");
		if ((read(f, d->textures[i]->pixels, w * h * 4)) < 0)
			print_err("Cannot read textures");
	}
}

static void	read_textures_name(t_data *d, int f)
{
	int		i;

	if (read(f, &d->nb_textures, sizeof(int32_t)) < 0)
		print_err("Cannot read texture nb");
	if (!(d->tex_name_list = (char**)malloc(sizeof(char*) * d->nb_textures)))
		print_err("Cannot allocate memory for texture names");
	i = -1;
	while (++i < d->nb_textures)
	{
		if (!(d->tex_name_list[i] = (char*)malloc(sizeof(char) * 100)))
			print_err("Cannot allocate memory for texture names");
		if (read(f, d->tex_name_list[i], 100) < 0)
			print_err("Cannot read texture list");
	}
}

/*
**	Read the number of sectors and walls
**	And get all the data structure
*/

static void	read_wall_n_sector_data(t_data *d, int f)
{
	int		i;

	if (read(f, &d->numsectors, sizeof(int16_t)) < 0)
		print_err("Cannot read nsectors");
	i = -1;
	while (++i < d->numsectors)
		if (read(f, &d->sectors[i], sizeof(t_sector)) < 0 ||
			read(f, d->sectors[i].floor_texture_name, 100) < 0 ||
			read(f, d->sectors[i].ceil_texture_name, 100) < 0)
			print_err("Cannot read sector struct");
	if (read(f, &d->numwalls, sizeof(int16_t)) < 0)
			print_err("Cannot read numwwalls");
	i = -1;
	while (++i < d->numwalls)
		if (read(f, &d->walls[i], sizeof(t_wall)) < 0 ||
			read(f, d->walls[i].texture_name, 100) < 0 ||
			read(f, d->walls[i].poster_name, 100) < 0)
			print_err("Cannot read wall structure");
}

int			contain_map_path(char *path)
{
	static char	check[] = PATH_MAP;

	if (ft_strncmp(path, &check[2], 5) == 0 ||
		ft_strncmp(path, PATH_MAP, 7) == 0)
		return (1);
	return (0);
}


void		load_map(t_data *d, char *map)
{
	int		f;
	char	*map_path;

	map_path = (contain_map_path(map)) ? ft_strdup(map) :
		ft_strjoin(PATH_MAP, map);
	if (((f = open(map_path, O_RDONLY)) == -1) ||
		read(f, &d->startcam.pos, sizeof(t_vec3f)) == -1 ||
		read(f, &d->startcam.rot, sizeof(double)) == -1 ||
		read(f, &d->startsectnum, sizeof(int16_t)) == -1 ||
		read(f, d->nextmap, 100) < 0)
		exit(printf("Doom : Map error\n"));

		read_wall_n_sector_data(d, f);
		read_monsters_data(d, f);
		read_assets_data(d, f);
		read_textures_name(d, f);
		read_texture_data(d, f);
		read_posters_data(d, f);
		load_weapons_texture(d, f, NB_TEX, NB_PROJECTILE);
		load_monsters_texture(d, f);
		read_assets_texture(d, f);
		load_sound(d, f);
	close(f);
	free(map_path);
}
