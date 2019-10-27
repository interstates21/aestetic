#include "../includes/doom_nukem.h"

void draw_message(t_data *d, char *message, int color, SDL_Rect rect)
{
	SDL_Surface *textSurface;
	SDL_Color	c;

	c.b = color & 0xFF;
	c.g = (color >> 8) & 0xFF;
	c.r = (color >> 16) & 0xFF;
	textSurface = TTF_RenderText_Solid(d->gFont, message , c);
	rect.x -= textSurface->w / 2;
	rect.y -= textSurface->h / 2;
	SDL_BlitSurface(textSurface, NULL, d->sdl.screen, &rect);
	SDL_FreeSurface(textSurface);
}

int	draw_background(t_data *d, SDL_Event e)
{
	static int active_option = 0;
	int color;

	SDL_FillRect(d->sdl.screen, NULL, 0x000000);
	color = active_option == 0 ? 0xFF0000 : 0xFFFFFF;
	draw_message(d, "NORMAL", color, (SDL_Rect){.x = WIDTH / 2, .y = HEIGHT / 2 - 30});
	color = active_option == 1 ? 0xFF0000 : 0xFFFFFF;
	draw_message(d, "HARD", color, (SDL_Rect){.x = WIDTH / 2, .y = HEIGHT / 2 + 20});
	SDL_UpdateWindowSurface(d->sdl.win);
	while (SDL_PollEvent(&e))
	{
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
				{
					if (active_option == 1)
						d->difficulty = 2;
					else
						d->difficulty = 1;
					d->tick = SDL_GetTicks();
					return (1);
				}
			}
	}
	return (0);
}

static void	render(t_data *d)
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
	render_sector(d, &d->sectors[d->cursectnum], &fr);
	draw_weapon(d);
	color_buffer(d);
	aiming_draw(d);
	draw_hud(d);
	SDL_UpdateWindowSurface(d->sdl.win);
}

void	loop(t_data *d)
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
