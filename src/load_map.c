/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:57:25 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	read_textures_name(t_env *d, int f)
{
	int		i;
	size_t	memory_size;
	size_t	sub_memory_size;

	if (read(f, &d->n_texts, sizeof(int32_t)) < 0)
		print_err("Cannot read texture nb");
	memory_size = sizeof(char*) * d->n_texts;
	d->tex_name_list = (char**)pure_malloc(memory_size,
		"cannot alloc texNames");
	i = -1;
	while (++i < d->n_texts)
	{
		sub_memory_size = sizeof(char) * 100;
		d->tex_name_list[i] = (char*)pure_malloc(sub_memory_size,
													"cannot alloc subTexNames");
		if (read(f, d->tex_name_list[i], 100) < 0)
			print_err("Cannot read texture list");
	}
}

static void	read_wall_n_sector_data(t_env *d, int f)
{
	int		i;

	if (read(f, &d->n_sect, sizeof(int16_t)) < 0)
		print_err("Cannot read nsectors");
	i = -1;
	while (++i < d->n_sect)
		if (read(f, &d->sectors[i], sizeof(t_sec)) < 0 ||
			read(f, d->sectors[i].floor_texture_name, 100) < 0 ||
			read(f, d->sectors[i].ceil_texture_name, 100) < 0)
			print_err("Cannot read sector struct");
	if (read(f, &d->n_walls, sizeof(int16_t)) < 0)
		print_err("Cannot read numwwalls");
	i = -1;
	while (++i < d->n_walls)
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

void		to_loading_map(t_env *d, char *map)
{
	int		f;
	char	*map_path;

	map_path = (contain_map_path(map)) ? ft_strdup(map) :
		ft_strjoin(PATH_MAP, map);
	if (((f = open(map_path, O_RDONLY)) == -1) ||
		read(f, &d->startcam.pos, sizeof(t_vec3f)) == -1 ||
		read(f, &d->startcam.rot, sizeof(double)) == -1 ||
		read(f, &d->sect_begin, sizeof(int16_t)) == -1 ||
		read(f, d->nextmap, 100) < 0)
		print_err("Doom : Map error\n");
	read_wall_n_sector_data(d, f);
	loading_data_monst(d, f);
	loading_data_asset(d, f);
	read_textures_name(d, f);
	read_texture_data(d, f);
	loading_data_post(d, f);
	loading_text_weap(d, f, NB_TEX, NB_PROJECTILE);
	loading_text_monst(d, f);
	loading_asset_text(d, f);
	music_loader(d, f);
	close(f);
	free(map_path);
}
