/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 02:27:59 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:09:46 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		music_loader(t_env *d, int f)
{
	int			i;
	int			rozm;
	uint8_t		*cache;
	SDL_RWops	*yyps;

	i = 0;
	if (d->chunk[0])
		return ;
	while (i++ < N_SOUNDS)
	{
		if (read(f, &rozm, sizeof(int)) < 0)
			print_err("cannot read sound data");
		cache = pure_malloc(rozm, "cannot alloc sound");
		if (read(f, cache, rozm) < 0)
			print_err("cannot read sound data");
		if (!(yyps = SDL_RWFromMem(cache, rozm)))
			print_err("cannot init sdl sound");
		if (!(d->chunk[i] = Mix_LoadWAV_RW(yyps, 1)))
			print_err("cannot init sdl sound chank");
		free(cache);
	}
}
