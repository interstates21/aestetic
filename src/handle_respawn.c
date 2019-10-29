/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_respawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:03:40 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:15:24 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	blackout(t_env *d)
{
	SDL_Event	e;

	play_sound(d, PLAYER_DEATH_SOUND, v3_to_v2(d->cam.pos));
	ft_memset(d->sdl.screen->pixels, 0,
	d->sdl.screen->pitch * d->sdl.screen->h);
	displaing_str(d, (t_font){ "YOU DIED\n \nR to Restart\nEsc to quit",
			WIDTH / 2 - 80, HEIGHT / 2 - 100, 0xffffff, 2});
	Mix_HaltChannel(99);
	SDL_UpdateWindowSurface(d->sdl.win);
	while (SDL_WaitEvent(&e))
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			exit(0);
		if (e.key.keysym.sym == SDLK_r)
			break ;
	}
}

void		respauning_h(t_env *d)
{
	int i;
	int j;

	blackout(d);
	monters_inicialization(d);
	play_initialization(d, &d->player);
	music_player(d, MAIN_MUSIC);
	i = -1;
	while (d->objects_n && ++i < d->n_sect)
	{
		j = -1;
		while (++j < d->objects[i][0].objects_n)
			d->objects[i][j].used = false;
	}
}
