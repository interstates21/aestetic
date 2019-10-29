/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:11:45 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 19:30:49 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		displaing_msg(t_env *d, char *message, int color, SDL_Rect rect)
{
	SDL_Surface *txtsurf;
	SDL_Color	c;

	c.b = color & 0xFF;
	c.g = (color >> 8) & 0xFF;
	c.r = (color >> 16) & 0xFF;
	txtsurf = TTF_RenderText_Solid(d->g_font, message, c);
	rect.x -= txtsurf->w / 2;
	rect.y -= txtsurf->h / 2;
	SDL_BlitSurface(txtsurf, NULL, d->sdl.screen, &rect);
	SDL_FreeSurface(txtsurf);
}

int			ini_dific(t_env *d, int active_option)
{
	if (active_option == 1)
	{
		d->hard = 2;
		d->tick = SDL_GetTicks();
		return (1);
	}
	else
	{
		d->hard = 1;
		d->tick = SDL_GetTicks();
		return (1);
	}
}

int			displaing_backgr(t_env *d, SDL_Event e)
{
	static int	active_option = 0;
	int			c;

	dm_exit(d, active_option, c);
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			print_and_quit(d, "RED CROSS");
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				print_and_quit(d, "ESC");
			if (e.key.keysym.sym == SDLK_DOWN)
				active_option--;
			if (e.key.keysym.sym == SDLK_UP)
				active_option++;
			if (active_option > 1)
				active_option = 0;
			if (active_option < 0)
				active_option = 1;
			if (e.key.keysym.sym == SDLK_RETURN)
				return (ini_dific(d, active_option));
		}
	}
	return (0);
}

static void	render(t_env *d)
{
	t_frustum	fr;
	int			i;

	fr.x1 = 0;
	fr.x2 = WIDTH - 1;
	ft_memset(fr.visitedportals, 0, sizeof(fr.visitedportals));
	i = -1;
	while (++i < WIDTH)
	{
		fr.ytop[i] = 0;
		fr.ybottom[i] = HEIGHT - 1;
	}
	i = -1;
	while (++i < WIDTH * HEIGHT)
		d->z_buff[i] = INFINITY;
	texture_pre_anim(d);
	sect_rendering(d, &d->sectors[d->this_sect], &fr);
	displaing_weap(d);
	buf_to_collor1(d);
	displaing_aiming(d);
	displaing_huds(d);
	SDL_UpdateWindowSurface(d->sdl.win);
}

void		loop(t_env *d)
{
	SDL_Event	e;
	uint32_t	start;

	to_load(d);
	music_player(d, MAIN_MUSIC);
	while (1)
	{
		start = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
				ev_keydown(d, e.key);
			if (e.type == SDL_MOUSEMOTION)
				ev_mot_mouse(d, e.motion);
			if (e.type == SDL_MOUSEBUTTONDOWN ||
					e.type == SDL_MOUSEBUTTONUP)
				ev_butt_mouse(d, e.button);
			if (e.type == SDL_QUIT)
				print_and_quit(d, "RED CROSS");
		}
		reloade(d);
		render(d);
		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}
