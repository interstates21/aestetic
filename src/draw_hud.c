/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 23:10:02 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 21:41:30 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	draw_ammo(t_data *d, t_weapon_type weapon_type)
{
	static char buf[100] = "Ammo: ";
	static char buf2[100] = "Health: ";

	ft_strcpy(buf + 6, ft_itoa_static(weapon_type.current_ammo));
	ft_strcpy(buf + ft_strlen(buf), " / ");
	ft_strcpy(buf + ft_strlen(buf), ft_itoa_static(MAX_BULLETS));
	draw_string(d, (t_font){buf, 50, 80, 0, 2});
	ft_strcpy(buf2 + 8, ft_itoa_static(d->player.health));
	draw_string(d, (t_font){buf2, 50, 50, 0, 2});
}

static void	draw_fuel(t_data *d)
{
	static char buf[100] = "Fuel: ";

	ft_strcpy(buf + 6, ft_itoa_static(d->player.is_flying));
	draw_string(d, (t_font){buf, 50, 110, 0, 2});
}

static void	draw_inventory_slot(t_data *d, SDL_Surface *tex, int x1, int y1)
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
				pixel_put(d, (t_vec3f){x1 + x_y.x, y1 + x_y.y, 0}, px, 0);
		}
	}
}

static void	draw_timed_msg(t_data *d)
{
	if (!d->msg[0])
		return ;
	draw_string(d, (t_font){d->msg, 50, HEIGHT - 180, 0, 2});
	if (SDL_GetTicks() - d->msg_start > 3000)
		d->msg[0] = 0;
}

void		draw_hud(t_data *d)
{
	if (d->slot2)
		draw_inventory_slot(d, d->assets_texture[d->slot2->picnum],
				140, HEIGHT - 100);
	draw_timed_msg(d);
	draw_ammo(d, d->weapon_type);
	if (d->player.is_flying)
		draw_fuel(d);
}
