/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 20:07:46 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 18:34:10 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	print_and_quit(t_data *d, const char *str)
{
	if (d->sdl.win)
		SDL_DestroyWindow(d->sdl.win);
	SDL_Quit();
	ft_putstr("Good Bye = ");
	ft_putendl(str);
	exit(0);
}

void	print_err(const char *err)
{
	ft_putstr("Init Error = ");
	ft_putendl(err);
	exit(1);
}

void	finish(t_data *d)
{
	SDL_Rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.h = HEIGHT;
	rect.w = WIDTH;
	SDL_FillRect(d->sdl.screen, NULL, 0x000000);
	draw_message(d, "FINISH", 0xFFFFFF,
		(SDL_Rect){.x = WIDTH / 2, .y = HEIGHT / 2 - 30});
	SDL_UpdateWindowSurface(d->sdl.win);
}
