/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_respawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:03:40 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 20:05:56 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

//notrefact

static void	blackout(t_data *d)
{
	SDL_Event	e;

	play_sound(d, PLAYER_DEATH_SOUND, v3_to_v2(d->cam.pos));
	ft_memset(d->sdl.screen->pixels, 0,
	d->sdl.screen->pitch * d->sdl.screen->h);
	draw_string(d, (t_font){ "YOU DIED\n \nR to Restart\nEsc to quit",
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

void		handle_respawn(t_data *d)
{
	int i;
	int j;

	blackout(d);
	init_monsters(d);
	init_player(d, &d->player);
	play_music(d, MAIN_MUSIC);
	i = -1;
	while (d->nb_assets && ++i < d->numsectors)
	{
		j = -1;
		while (++j < d->assets[i][0].nb_assets)
			d->assets[i][j].used = false;
	}
}
