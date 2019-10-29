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

static void	text_whi_le(t_env *d, int f, int num)
{
	int		i;
	int		wid;
	int		heig;

	i = -1;
	if (num == 1)
	{
		while (++i < d->n_texts)
		{
			if (read(f, &wid, sizeof(int)) < 0)
				print_err("Cannot read texture size");
			if (read(f, &heig, sizeof(int)) < 0)
				print_err("Cannot read texture size");
			if (!(d->texts[i] = SDL_CreateRGBSurfaceWithFormat(
				0, wid, heig, 32, SDL_PIXELFORMAT_ARGB8888)))
				print_err("Cannot create texture surface");
			if ((read(f, d->texts[i]->pixels, wid * heig * 4)) < 0)
				print_err("Cannot read texts");
		}
	}
}

void		read_texture_data(t_env *d, int f)
{
	size_t	tex_size;

	tex_size = sizeof(SDL_Surface*) * d->n_texts;
	d->texts = (SDL_Surface**)pure_malloc(tex_size,
		"cannot alloc tex memory");
	text_whi_le(d, f, 1);
}
