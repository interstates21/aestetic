/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:07:52 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 22:02:32 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_vec3f		trans_v3f_in_scr(t_data *d, t_vec3f v)
{
	t_vec3f	new;

	new = v3_min(v, d->cam.pos);
	new = new_v3(
		new.x * d->cam.cos - new.z * d->cam.sin,
			new.y,
			new.x * d->cam.sin + new.z * d->cam.cos
	);
	new.x /= new.z;
	new.y /= new.z;
	new.x = new.x * WIDTH + WIDTH * 0.5;
	new.y = new.y * -WIDTH + HEIGHT * 0.5 - d->cam.y_offset;
	return (new);
}

static void	new_disp_data(t_frustum *fr, t_display_data *disp_data,
		uint16_t cursectnum)
{
	double large_x;
	double large_y;

	large_x = disp_data->start.x - disp_data->end.x;
	large_y = disp_data->start.y - disp_data->end.y;
	disp_data->scale.x = fabs(100.0 / large_x * 0.01);
	disp_data->cut_start = MAX(disp_data->start.x, fr->x1);
	disp_data->cut_end = MIN(disp_data->end.x, fr->x2);
	disp_data->scale.y = fabs(100.0 / large_y * 0.01);
	disp_data->ytop = &fr->ytop[0];
	disp_data->ybot = &fr->ybottom[0];
	disp_data->cursectnum = cursectnum;
}

void		draw_projectile(t_data *d, t_frustum *fr,
		t_projectile proj)
{
	double			dist;
	t_display_data	a;
	t_vec3f			point_in_screen;

	point_in_screen = trans_v3f_in_scr(d, proj.pos);
	if (point_in_screen.z <= 0)
		return ;
	dist = vec3f_length(v3_min(proj.pos, d->cam.pos));
	a.start.x = point_in_screen.x - (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->w *
			d->projectile_type[proj.id_type].size) / dist;
	a.end.x = point_in_screen.x + (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->w *
			d->projectile_type[proj.id_type].size) / dist;
	a.start.y = point_in_screen.y - (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->h *
			d->projectile_type[proj.id_type].size) / dist;
	a.end.y = point_in_screen.y + (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->h *
			d->projectile_type[proj.id_type].size) / dist;
	new_disp_data(fr, &a, proj.cursectnum);
	disp_sprite(d, d->projectile_tex[proj.id_type]
			[proj.current_anim_playing], a, new_v2(point_in_screen.z, 2));
}

void		disp_sprite(t_data *d, SDL_Surface *s,
		t_display_data disp_data, t_vec2f dist_mod)
{
	t_vec2		x_y;
	uint32_t	colo;

	x_y.x = disp_data.cut_start - 1;
	while (++x_y.x <= disp_data.cut_end)
	{
		x_y.y = dist_mod.y == 2 ? MAX(disp_data.ytop[x_y.x],
			disp_data.start.y) - 1 : MAX(0, disp_data.start.y) - 1;
		while (++x_y.y <= MIN(dist_mod.y == 2 ? disp_data.ybot[x_y.x] :
												HEIGHT - 1, disp_data.end.y))
		{
			if (dist_mod.x >= d->zbuffer[x_y.x + x_y.y * d->sdl.screen->w]
														&& dist_mod.y < 2)
				continue;
			colo = pixel_pls(s, dist_mod.y == 0 ?
				1 - (disp_data.scale.x * (x_y.x - disp_data.start.x)) :
					disp_data.scale.x * (x_y.x - disp_data.start.x),
			disp_data.scale.y * (x_y.y - disp_data.start.y), 0);
			colo = alpha(((uint32_t *)d->sdl.screen->pixels)
					[x_y.x + x_y.y * d->sdl.screen->w], colo);
			if (colo != pixel_pls(d->sdl.screen, x_y.x, x_y.y, 2))
				new_zbuffer_and_put_collor(d, x_y, shade(shd_fct(d, &d->sectors[disp_data.cursectnum], dist_mod.x, 0), colo), dist_mod);
		}
	}
}

void		draw_sprite(t_data *d, t_frustum *fr, t_sprite_list *sprite)
{
	if (sprite->type == IS_MONSTER)
		draw_monster(d, d->monsters[sprite->id]);
	if (sprite->type == IS_PROJECTILE)
		draw_projectile(d, fr, d->projectiles[sprite->id]);
}
