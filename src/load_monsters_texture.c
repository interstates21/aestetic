/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_monsters_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:41:36 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/27 02:27:47 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	read_motherdemon_projectile(t_data *d, int f)
{
	int		i;
	int		wid;
	int		heig;

	i = -1;
	while (++i < 5)
	{
		if (read(f, &wid, sizeof(int)) < 0 || read(f, &heig, sizeof(int)) < 0 ||
			!(d->projectile_tex[1][i] = SDL_CreateRGBSurfaceWithFormat(
									0, wid, heig, 32, SDL_PIXELFORMAT_ARGB8888)) ||
			read(f, d->projectile_tex[1][i]->pixels, wid * heig * 4) < 0)
			print_err("Failed to read motherdemon projectile\n");
	}
}

static int	read_anim_death_texture(t_data *d, int f, int *i, int nb_o)
{
	int	o;
	int	w;
	int	h;

	if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
		print_err("Some Error");
		return (printf("Failed to read death texture size.\n"));
	if (!(d->monster_text[i[0]][i[1]][0] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
		return (printf("Failed to create monster death SDL_Surface.\n"));
	if (read(f, d->monster_text[i[0]][i[1]][0]->pixels, w * h * 4) < 0)
		return (printf("Failed to read monster texture.\n"));
	o = 0;
	while (++o < nb_o)
		d->monster_text[i[0]][i[1]][o] = d->monster_text[i[0]][i[1]][0];
	return (0);
}

static int	read_anim_texture(t_data *d, int f, int *i, int nb_o)
{
	int	o;
	int	w;
	int	h;

	o = -1;
	while (++o < nb_o)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			return (printf("Failed to read texture size.\n"));
		if (!(d->monster_text[i[0]][i[1]][o] = SDL_CreateRGBSurfaceWithFormat(
									0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (printf("Failed to create monster anim SDL_Surface.\n"));
		if (read(f, d->monster_text[i[0]][i[1]][o]->pixels, w * h * 4) < 0)
			return (printf("Failed to read monster texture.\n"));
	}
	return (0);
}

static void load_whi_le(t_data *d, int f, int i, int nb_orientation)
{
	int a;

	a = -1;
	while (++a < 7)
		if (read_anim_texture(d, f, (int[2]){i, a}, nb_orientation))
			print_err("monst error");
}

void			load_monsters_texture(t_data *d, int f)
{
	int i;
	int a;
	int nb_orientation;
	int	nb_death;

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
			if (read_anim_death_texture(d, f, (int[2]){i, a}, nb_orientation))
				print_err("cannot react anim death");
	}
	read_motherdemon_projectile(d, f);
	print_err("cannot read demon");
}
