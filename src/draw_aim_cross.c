/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_aim_cross.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:25:37 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 21:31:32 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	load_tex(t_data *d, t_three_val cont, int *tex)
{
	int	j;
	int	w;
	int	h;

	j = -1;
	while (++j < tex[cont.two])
	{
		if (read(cont.one, &w, sizeof(int)) < 0 ||
			read(cont.one, &h, sizeof(int)) < 0 ||
			(cont.three == 0 ?
				!(d->weapon_tex[cont.two][j] =
					SDL_CreateRGBSurfaceWithFormat(0, w, h, 32,
						SDL_PIXELFORMAT_ARGB8888)) :
				!(d->projectile_tex[cont.two][j] =
					SDL_CreateRGBSurfaceWithFormat(0, w, h, 32,
						SDL_PIXELFORMAT_ARGB8888))) ||
			read(cont.one, cont.three == 0 ?
				d->weapon_tex[cont.two][j]->pixels :
				d->projectile_tex[cont.two][j]->pixels, w * h * 4) < 0)
			cont.three == 0 ? print_err("cannot read num weapon") :
								print_err("cannot read texture projectile");
	}
}

void	load_weapons_texture(t_data *d, int f, int *nb_tex,
								int *nb_projectiles)
{
	t_three_val	container;

	container.one = f;
	container.two = -1;
	while (++container.two < 3)
	{
		container.three = 0;
		load_tex(d, container, nb_tex);
		container.three = 1;
		load_tex(d, container, nb_projectiles);
	}
}

void	drawing(t_data *d, uint32_t colo, int mode)
{
	short		i;

	if (mode == 0)
	{
		i = -1;
		while (++i < 10)
			pixel_put(d, new_v3((WIDTH / 2) - 16 + i, HEIGHT / 2, 0),
																	colo, 0);
		i += 12;
		while (++i < 32)
			pixel_put(d, new_v3((WIDTH / 2) - 16 + i, HEIGHT / 2, 0),
																	colo, 0);
	}
	else
	{
		i = -1;
		while (++i < 10)
			pixel_put(d, new_v3(WIDTH / 2, (HEIGHT / 2) - 16 + i, 0),
																	colo, 0);
		i += 12;
		while (++i < 32)
			pixel_put(d, new_v3(WIDTH / 2, (HEIGHT / 2) - 16 + i, 0),
																	colo, 0);
	}
}

void	draw_aim_cross(t_data *d)
{
	uint32_t	colo;

	if (d->player.current_weapon == CRYO_BALLISTA)
		colo = 0xDDFF;
	drawing(d, colo, 0);
	pixel_put(d, new_v3(WIDTH / 2, HEIGHT / 2, 0), colo, 0);
}
