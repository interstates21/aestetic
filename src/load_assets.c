/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:56:36 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		post_whi_le(t_env *d, int f, int b)
{
	int		i;
	int		wid;
	int		heig;

	i = -1;
	if (b == 1)
	{
		while (++i < d->n_posters)
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
		while (++i < d->monst_n)
			if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
				print_err("Cannot read monsters data");
	}
}

void		loading_data_post(t_env *d, int f)
{
	size_t	posters_size;

	if (read(f, &d->n_posters, sizeof(int32_t)) < 0)
		print_err("Cannot read num posters");
	if (d->n_posters <= 0)
		return ;
	posters_size = sizeof(SDL_Surface*) * d->n_posters;
	d->posters = (SDL_Surface**)pure_malloc(posters_size,
												"Cannot alloc posters");
	post_whi_le(d, f, 1);
}

void		loading_data_monst(t_env *d, int f)
{
	int		i;
	size_t	monsters_size;

	if (read(f, &d->monst_n, sizeof(uint16_t)) < 0)
		print_err("Cannot read num monsters");
	if (d->monst_n > 0)
	{
		monsters_size = sizeof(t_monster) * d->monst_n;
		d->monsters = (t_monster*)pure_malloc(monsters_size,
												"cannot alloc monsters");
		i = -1;
		post_whi_le(d, f, 2);
	}
}

void		loading_asset_text(t_env *d, int f)
{
	int		i;
	int		w;
	int		h;
	size_t	assets_size;

	if (read(f, &d->nb_assets_texture, sizeof(int16_t)) < 0)
		print_err("Cannot read num objects");
	if (d->nb_assets_texture <= 0)
		return ;
	assets_size = sizeof(SDL_Surface*) * d->nb_assets_texture;
	d->assets_texture = (SDL_Surface**)pure_malloc(assets_size,
												"cannot alloc objects");
	i = -1;
	while (++i < d->nb_assets_texture)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Cannot read asset size");
		if (!(d->assets_texture[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Cannot alloc objects");
		if ((read(f, d->assets_texture[i]->pixels, w * h * 4)) < 0)
			print_err("Cannot read asset texture");
	}
}

void		loading_data_asset(t_env *d, int f)
{
	int		i;
	int		s;
	size_t	assets_size;
	size_t	sub_assets_size;

	if (read(f, &d->objects_n, sizeof(int16_t)) < 0)
		print_err("Cannot read objects num");
	assets_size = sizeof(t_objects*) * d->n_sect;
	d->objects = (t_objects**)pure_malloc(assets_size, "cannot alloc objects");
	if (d->objects_n > 0)
	{
		s = -1;
		while (++s < d->n_sect)
		{
			sub_assets_size = sizeof(t_objects) * 10;
			d->objects[s] = (t_objects*)pure_malloc(sub_assets_size,
												"cannot alloc subAssets");
			if (read(f, &d->objects[s][0].objects_n, sizeof(int)) < 0)
				print_err("Cannot read nb asset for sect");
			i = -1;
			while (++i < d->objects[s][0].objects_n)
				if (read(f, &d->objects[s][i], sizeof(t_objects)) < 0)
					print_err("Cannot read asset[][]");
		}
	}
}
