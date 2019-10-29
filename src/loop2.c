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

void		dm_exit(t_env *d, int active_option, int c)
{
	SDL_FillRect(d->sdl.screen, NULL, 0x000000);
	c = active_option == 0 ? 0xFF0000 : 0xFFFFFF;
	displaing_msg(d, "NRM", c, (SDL_Rect){.x = WIDTH / 2,
	.y = HEIGHT / 2 - 30});
	c = active_option == 1 ? 0xFF0000 : 0xFFFFFF;
	displaing_msg(d, "HRD", c, (SDL_Rect){.x = WIDTH / 2,
	.y = HEIGHT / 2 + 20});
	SDL_UpdateWindowSurface(d->sdl.win);
}
