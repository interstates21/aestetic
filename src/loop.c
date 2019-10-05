#include "../includes/doom_nukem.h"

void	render(t_data *d)
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
	draw_aim_cross(d);
	draw_hud(d);
	SDL_UpdateWindowSurface(d->win);
}

void	loop(t_data *d)
{
	SDL_Event	e;
	uint32_t	start;

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
				proper_exit(d);
		}
		update(d);
		render(d);
		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}
