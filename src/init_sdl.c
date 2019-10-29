/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:46:16 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	x_cm(t_env *d, int pos_r)
{
	int		i;

	i = -1;
	while (++i < d->n_sect && (pos_r = -1))
		while (++pos_r < d->n_texts)
		{
			if (ft_strequ(d->sectors[i].floor_texture_name,
													d->tex_name_list[pos_r]))
				d->sectors[i].floorpicnum = pos_r;
			if (ft_strequ(d->sectors[i].ceil_texture_name,
													d->tex_name_list[pos_r]))
				d->sectors[i].ceilpicnum = pos_r;
		}
}

void	to_load_numbpic(t_env *d)
{
	int		i;
	int		pos_r;

	i = -1;
	while (++i < d->n_walls && (pos_r = -1))
		while (++pos_r < d->n_texts)
			if (ft_strequ(d->walls[i].texture_name, d->tex_name_list[pos_r]))
			{
				d->walls[i].lowerpicnum = pos_r;
				d->walls[i].middlepicnum = pos_r;
				d->walls[i].upperpicnum = pos_r;
			}
	x_cm(d, pos_r);
}

void	sdl_inicialization(t_sdl *sdl)
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

void	keyboard_battons(Uint8 **keys)
{
	*(keys) = (Uint8*)SDL_GetKeyboardState(NULL);
}
