/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 23:00:02 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	x_cm(t_data *d, int pos_r)
{
	int		i;

	i = -1;
	while (++i < d->numsectors && (pos_r = -1))
		while (++pos_r < d->nb_textures)
		{
			if (ft_strequ(d->sectors[i].floor_texture_name,
													d->tex_name_list[pos_r]))
				d->sectors[i].floorpicnum = pos_r;
			if (ft_strequ(d->sectors[i].ceil_texture_name,
													d->tex_name_list[pos_r]))
				d->sectors[i].ceilpicnum = pos_r;
		}
}

void	fix_picnum(t_data *d)
{
	int		i;
	int		pos_r;

	i = -1;
	while (++i < d->numwalls && (pos_r = -1))
		while (++pos_r < d->nb_textures)
			if (ft_strequ(d->walls[i].texture_name, d->tex_name_list[pos_r]))
			{
				d->walls[i].lowerpicnum = pos_r;
				d->walls[i].middlepicnum = pos_r;
				d->walls[i].upperpicnum = pos_r;
			}
	x_cm(d, pos_r);
}

void	init_sdl(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(sdl->win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0)))
		print_err(SDL_GetError());
	if (!(sdl->screen = SDL_GetWindowSurface(sdl->win)))
		print_err(SDL_GetError());
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)
	== -1)
		print_err(SDL_GetError());
	if (!Mix_AllocateChannels(MAX_CHANNELS))
		print_err(SDL_GetError());
}

void	init_keys(Uint8 **keys)
{
	*(keys) = (Uint8*)SDL_GetKeyboardState(NULL);
}
