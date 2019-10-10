
#include "editor.h"

int			contain_map_path(char *path)
{
	char	*check;

	check = PATH_MAP;
	if (ft_strncmp(path, &check[2], 5) == 0)
		return (1);
	if (ft_strncmp(path, PATH_MAP, 7) == 0)
		return (2);
	return (0);
}

static void	fix_monster_list(t_data *d)
{
	int		i;
	int		nb;

	i = -1;
	nb = d->nbmonsters;
	d->nbmonsters = 0;
	d->interface.selected_asset_cat = 1;
	while (++i < nb)
	{
		d->interface.selected_asset = d->monsters[i].id_type;
		add_monster_to_list(d, &d->monsters[i].pos, d->monsters[i].cursectnum,
															&d->interface);
	}
	d->interface.selected_asset = -1;
}

static int	read_monsters_data(t_data *d, int f)
{
	int	i;

	if (read(f, &d->nbmonsters, sizeof(uint16_t)) < 0)
		return (printf("Failed to read nummonsters.\n"));
	if (d->nbmonsters > 0)
	{
		if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) *
														d->nbmonsters)))
			return (printf("Failed to allocate monster stucture.n"));
		i = -1;
		while (++i < d->nbmonsters)
			if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
				return (printf("Failed to read monsters.\n"));
	}
	return (0);
}

/*
**	Read the number of sectors and walls
**	And get all the data structure
*/

static int	read_wall_n_sector_data(t_data *d, int f)
{
	int		i;

	if (read(f, &d->numsectors, sizeof(int16_t)) < 0)
		return (printf("Failed to read numsectors.\n"));
	i = -1;
	while (++i < d->numsectors)
		if (read(f, &d->sectors[i], sizeof(t_sector)) < 0 ||
			read(f, d->sectors[i].floor_texture_name, 100) < 0 ||
			read(f, d->sectors[i].ceil_texture_name, 100) < 0)
			return (printf("Failed to read sector structure.\n"));
	if (read(f, &d->numwalls, sizeof(int16_t)) < 0)
		return (printf("Faield to read numwwalls.\n"));
	i = -1;
	while (++i < d->numwalls)
	{
		if (read(f, &d->walls[i], sizeof(t_wall)) < 0 ||
			read(f, d->walls[i].texture_name, 100) < 0 ||
			read(f, d->walls[i].poster_name, 100) < 0)
			return (printf("Failed to read wall structure.\n"));
		if (d->walls[i].is_door)
			d->nb_door++;
	}
	return (0);
}

/*
**  camrot not use in editor but the data exist in map file cause it's need
**  for doom.
*/

int			load_map(t_data *d, char *map)
{
	int			f;
	double		camrot;
	struct stat	sb;

	map = (contain_map_path(map)) ? map : ft_strjoin(PATH_MAP, map);
	camrot = 0;
	if (((f = open(map, O_RDONLY)) < 0) || (fstat(f, &sb) == -1) ||
		((sb.st_mode & S_IFMT) != S_IFREG) ||
		read(f, &d->player_start, sizeof(t_vec3f)) < 0 ||
		read(f, &camrot, sizeof(double)) < 0 ||
		read(f, &d->startsectnum, sizeof(int16_t)) < 0 ||
		read(f, d->next_map, 100) < 0)
		return (printf("# Map ERROR !\n"));
	if (!map_exist(d, d->next_map, d->next_map))
		ft_memset(d->next_map, 0, 100);
	if (read_wall_n_sector_data(d, f) || read_monsters_data(d, f) ||
		read_assets_data(d, f))
		return (1);
	fix_picnum(d, NULL);
	close(f);
	if (!(contain_map_path(map)))
		free(map);
	fix_monster_list(d);
	return (0);
}
