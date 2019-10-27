/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_jetp_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 23:10:02 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 22:42:36 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	draw_fuel(t_data *d)
{
	static char buf[100] = "Fuel: ";

	ft_strcpy(buf + 6, ft_itoa_static(d->player.is_flying));
	draw_string(d, (t_font){buf, 50, 110, 0, 2});
}

void	draw_inventory_slot(t_data *d, SDL_Surface *tex, int x1, int y1)
{
	uint32_t	px;
	t_vec2		x_y;
	t_vec2		h_u;
	double		pix_yh;

	h_u.x = SLOT_W * (double)tex->h / tex->w;
	x_y.x = -1;
	while (++x_y.x < SLOT_W)
	{
		h_u.y = ((double)x_y.x / SLOT_W) * tex->w;
		x_y.y = -1;
		while (++x_y.y < h_u.x)
		{
			pix_yh = (double)x_y.y / h_u.x;
			if (((px = pixel_pls(tex, h_u.y, pix_yh, 3)) >> 24) > 127)
				pixel_put(d, new_v3(x1 + x_y.x, y1 + x_y.y, 0), px, 0);
		}
	}
}
