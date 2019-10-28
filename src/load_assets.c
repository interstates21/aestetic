/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/28 20:22:10 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		post_whi_le(t_data *d, int f, int b)
{
	int		i;
	int		wid;
	int		heig;

	i = -1;
	if (b == 1)
	{
		while (++i < d->nb_posters)
		{
			if (read(f, &wid, sizeof(int)) < 0 || read(f, &heig,
				sizeof(int)) < 0)
				print_err("Cannot read posters size");
			if (!(d->posters[i] = SDL_CreateRGBSurfaceWithFormat(
				0, wid, heig, 32, SDL_PIXELFORMAT_ARGB8888)))
				print_err("Cannot allocate posters");
			if ((read(f, d->posters[i]->pixels, wid * heig * 4)) < 0)
				print_err("Cannot read poster data");
		}
	}
	else if (b == 2)
	{
		while (++i < d->nummonsters)
			if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
				print_err("Cannot read monsters data");
	}
}

void		read_posters_data(t_data *d, int f)
{
	size_t	posters_size;

	if (read(f, &d->nb_posters, sizeof(int32_t)) < 0)
		print_err("Cannot read num posters");
	if (d->nb_posters <= 0)
		return ;
	posters_size = sizeof(SDL_Surface*) * d->nb_posters;
	d->posters = (SDL_Surface**)pure_malloc(posters_size,
												"Cannot alloc posters");
	post_whi_le(d, f, 1);
}

void		read_monsters_data(t_data *d, int f)
{
	int		i;
	size_t	monsters_size;

	if (read(f, &d->nummonsters, sizeof(uint16_t)) < 0)
		print_err("Cannot read num monsters");
	if (d->nummonsters > 0)
	{
		monsters_size = sizeof(t_monster) * d->nummonsters;
		d->monsters = (t_monster*)pure_malloc(monsters_size,
												"cannot alloc monsters");
		i = -1;
		post_whi_le(d, f, 2);
	}
}

void		read_assets_texture(t_data *d, int f)
{
	int		i;
	int		w;
	int		h;
	size_t	assets_size;

	if (read(f, &d->nb_assets_texture, sizeof(int16_t)) < 0)
		print_err("Cannot read num assets");
	if (d->nb_assets_texture <= 0)
		return ;
	assets_size = sizeof(SDL_Surface*) * d->nb_assets_texture;
	d->assets_texture = (SDL_Surface**)pure_malloc(assets_size,
												"cannot alloc assets");
	i = -1;
	while (++i < d->nb_assets_texture)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Cannot read asset size");
		if (!(d->assets_texture[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Cannot alloc assets");
		if ((read(f, d->assets_texture[i]->pixels, w * h * 4)) < 0)
			print_err("Cannot read asset texture");
	}
}

void		read_assets_data(t_data *d, int f)
{
	int		i;
	int		s;
	size_t	assets_size;
	size_t	sub_assets_size;

	if (read(f, &d->nb_assets, sizeof(int16_t)) < 0)
		print_err("Cannot read assets num");
	assets_size = sizeof(t_assets*) * d->numsectors;
	d->assets = (t_assets**)pure_malloc(assets_size, "cannot alloc assets");
	if (d->nb_assets > 0)
	{
		s = -1;
		while (++s < d->numsectors)
		{
			sub_assets_size = sizeof(t_assets) * 10;
			d->assets[s] = (t_assets*)pure_malloc(sub_assets_size,
												"cannot alloc subAssets");
			if (read(f, &d->assets[s][0].nb_assets, sizeof(int)) < 0)
				print_err("Cannot read nb asset for sect");
			i = -1;
			while (++i < d->assets[s][0].nb_assets)
				if (read(f, &d->assets[s][i], sizeof(t_assets)) < 0)
					print_err("Cannot read asset[][]");
		}
	}
}
