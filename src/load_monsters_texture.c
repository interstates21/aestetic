/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_monsters_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:57:09 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	read_motherdemon_projectile(t_env *d, int f)
{
	int		i;
	int		wid;
	int		heig;

	i = -1;
	while (++i < 5)
	{
		if (read(f, &wid, sizeof(int)) < 0 || read(f, &heig, sizeof(int)) < 0 ||
			!(d->anim_rot_text[1][i] = SDL_CreateRGBSurfaceWithFormat(
				0, wid, heig, 32, SDL_PIXELFORMAT_ARGB8888)) ||
			read(f, d->anim_rot_text[1][i]->pixels, wid * heig * 4) < 0)
			print_err("Failed to read motherdemon projectile\n");
	}
}

static void	read_anim_death_texture(t_env *d, int f, int *i, int nb_o)
{
	int		o;
	int		w;
	int		h;

	if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
		print_err("Some Error");
	if (!(d->monster_text[i[0]][i[1]][0] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
		print_err("Some Error");
	if (read(f, d->monster_text[i[0]][i[1]][0]->pixels, w * h * 4) < 0)
		print_err("Some Error");
	o = 0;
	while (++o < nb_o)
		d->monster_text[i[0]][i[1]][o] = d->monster_text[i[0]][i[1]][0];
}

static void	read_anim_texture(t_env *d, int f, int *i, int nb_o)
{
	int		o;
	int		w;
	int		h;

	o = -1;
	while (++o < nb_o)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			print_err("Some Error");
		if (!(d->monster_text[i[0]][i[1]][o] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			print_err("Some Error");
		if (read(f, d->monster_text[i[0]][i[1]][o]->pixels, w * h * 4) < 0)
			print_err("Some Error");
	}
}

static void	load_whi_le(t_env *d, int f, int i, int nb_orientation)
{
	int		a;

	a = -1;
	while (++a < 7)
		read_anim_texture(d, f, (int[2]){i, a}, nb_orientation);
}

void		loading_text_monst(t_env *d, int f)
{
	int		i;
	int		a;
	int		nb_orientation;
	int		nb_death;

	i = -1;
	while (++i < 2)
	{
		if (read(f, &nb_orientation, sizeof(int)) < 0)
			print_err("cannot read num orientation monsters");
		load_whi_le(d, f, i, nb_orientation);
		if (read(f, &nb_death, sizeof(int)) < 0)
			print_err("cannot read num death");
		a = 18 - nb_death;
		while (++a < 19)
			read_anim_death_texture(d, f, (int[2]){i, a}, nb_orientation);
	}
	read_motherdemon_projectile(d, f);
}
