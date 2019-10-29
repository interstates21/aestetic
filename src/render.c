/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:40:05 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 16:07:47 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	render(t_env *d)
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
