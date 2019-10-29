/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:59:42 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:59:11 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static int	get_col(int p, int s)
{
	if (s <= p)
		return (0x00aa00);
	return (0x333333);
}

static int	to_percent(int p)
{
	int		r;

	r = (int)(p / 100);
	return (r > 100 ? 100 : r);
}

static void	draw_bar(t_env *d, int p)
{
	int		start;
	int		end;
	int		i;
	int		j;
	int		col;

	ft_memset(d->sdl.screen->pixels, 0,
	d->sdl.screen->pitch * d->sdl.screen->h);
	start = (WIDTH >> 1) - 50;
	end = start + 100;
	i = start - 1;
	while (++i < end && (j = -1))
		while (++j < 5)
		{
			col = get_col(to_percent(p), i - start);
			pixel_put(d, new_v3(i, j + (HEIGHT >> 1), 0), col, 0);
		}
}

void		correct_loading(t_env *d, uint32_t *status, SDL_Event e)
{
	char		*num;
	char		*str;
	char		*tmp;

	status[1] = SDL_GetTicks() - d->tick;
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			print_and_quit(d, "RED CROSS");
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			print_and_quit(d, "ESC");
	str = ft_strdup("LOADING ");
	tmp = str;
	num = ft_itoa(to_percent(status[1]));
	str = ft_strjoin(str, num);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, "%");
	free(tmp);
	free(num);
	draw_bar(d, status[1]);
	displaing_str(d, (t_font){ str, (WIDTH >> 1) - 56,
									(HEIGHT >> 1) - 42, 0xaaaaaa, 2 });
	free(str);
	SDL_UpdateWindowSurface(d->sdl.win);
}

void		to_load(t_env *d)
{
	uint32_t	status[2];
	SDL_Event	e;

	status[0] = 0;
	status[1] = status[0];
	if (d->loaded)
		return ;
	while (status[1] - status[0] < 10000 || SDL_PollEvent(&e))
		correct_loading(d, status, e);
	d->loaded = 1;
}
