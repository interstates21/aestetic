/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:11:45 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/28 21:49:35 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void		draw_message(t_env *d, char *message, int color, SDL_Rect rect)
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

int			draw_background(t_env *d, SDL_Event e)
{
	static int	active_option = 0;
	int			c;

	SDL_FillRect(d->sdl.screen, NULL, 0x000000);
	c = active_option == 0 ? 0xFF0000 : 0xFFFFFF;
	draw_message(d, "NRM", c, (SDL_Rect){.x = WIDTH / 2, .y = HEIGHT / 2 - 30});
	c = active_option == 1 ? 0xFF0000 : 0xFFFFFF;
	draw_message(d, "HRD", c, (SDL_Rect){.x = WIDTH / 2, .y = HEIGHT / 2 + 20});
	SDL_UpdateWindowSurface(d->sdl.win);
	while (SDL_PollEvent(&e))
		if (e.type == SDL_KEYDOWN)
		{
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
		d->zbuffer[i] = INFINITY;
	precompute_texanim(d);
	render_sector(d, &d->sectors[d->this_sect], &fr);
	draw_weapon(d);
	color_buffer(d);
	aiming_draw(d);
	draw_hud(d);
	SDL_UpdateWindowSurface(d->sdl.win);
}

void		loop(t_env *d)
{
	SDL_Event	e;
	uint32_t	start;

	loading(d);
	play_music(d, MAIN_MUSIC);
	while (1)
	{
		start = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
				event_key_down(d, e.key);
			if (e.type == SDL_MOUSEMOTION)
				event_mouse_motion(d, e.motion);
			if (e.type == SDL_MOUSEBUTTONDOWN ||
					e.type == SDL_MOUSEBUTTONUP)
				event_mouse_button(d, e.button);
			if (e.type == SDL_QUIT)
				print_and_quit(d, "RED CROSS");
		}
		update(d);
		render(d);
		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}
