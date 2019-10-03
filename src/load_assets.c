/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:04:36 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/09 17:04:37 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int		read_posters_data(t_data *d, int f)
{
	int	i;
	int w;
	int h;

	if (read(f, &d->nb_posters, sizeof(int32_t)) < 0)
		return (printf("Error read nb posters.\n"));
	if (d->nb_posters <= 0)
		return (0);
	if (!(d->posters =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_posters)))
		return (printf("Malloc posters texture fail"));
	i = -1;
	while (++i < d->nb_posters)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			return (printf("Failed to read posters size\n"));
		if (!(d->posters[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (printf("Failed to allocate posters surface\n"));
		if ((read(f, d->posters[i]->pixels, w * h * 4)) < 0)
			return (printf("Read posters data failed\n"));
	}
	return (0);
}

int		read_monsters_data(t_data *d, int f)
{
	int	i;

	if (read(f, &d->nummonsters, sizeof(uint16_t)) < 0)
		return (printf("Failed to read nummonsters.\n"));
	if (d->nummonsters > 0)
	{
		if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) *
														d->nummonsters)))
			return (printf("Failed to allocate monster stucture.n"));
		i = -1;
		while (++i < d->nummonsters)
			if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
				return (printf("Failed to read monsters.\n"));
	}
	return (0);
}

int		read_assets_texture(t_data *d, int f)
{
	int	i;
	int	w;
	int	h;

	if (read(f, &d->nb_assets_texture, sizeof(int16_t)) < 0)
		return (printf("Failed to read nb_assets_texture.\n"));
	if (d->nb_assets_texture <= 0)
		return (0);
	if (!(d->assets_texture =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_assets_texture)))
		return (printf("Malloc asset texture fail"));
	i = -1;
	while (++i < d->nb_assets_texture)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			return (printf("Failed to read asset texture size.\n"));
		if (!(d->assets_texture[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (printf("Failed to allocate asset surface\n"));
		if ((read(f, d->assets_texture[i]->pixels, w * h * 4)) < 0)
			return (printf("Failed to read asset texture %d.\n", i));
	}
	return (0);
}

int		read_assets_data(t_data *d, int f)
{
	int	i;
	int	s;

	if (read(f, &d->nb_assets, sizeof(int16_t)) < 0)
		return (printf("Failed to read nb_assets.\n"));
	if (!(d->assets = (t_assets**)malloc(sizeof(t_assets*) * d->numsectors)))
		return (printf("Failed to malloc assets structures.\n"));
	if (d->nb_assets > 0)
	{
		s = -1;
		while (++s < d->numsectors)
		{
			if (!(d->assets[s] = (t_assets*)malloc(sizeof(t_assets) * 10)))
				return (printf("Failed to malloc assets structures.\n"));
			if (read(f, &d->assets[s][0].nb_assets, sizeof(int)) < 0)
				return (printf("Failed to read nb_assets for sector.\n"));
			i = -1;
			while (++i < d->assets[s][0].nb_assets)
				if (read(f, &d->assets[s][i], sizeof(t_assets)) < 0)
					return (printf("Failed to read d->asset[][].\n"));
		}
	}
	return (0);
}
