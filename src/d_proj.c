/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_proj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:19:18 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:42:40 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_vec3f		v3f_transpar(t_env *d, t_vec3f v)
{
	t_vec3f	new;

	new = v3_min(v, d->cam.pos);
	new = new_v3(
		new.x * d->cam.cos - new.z * d->cam.sin,
			new.y,
			new.x * d->cam.sin + new.z * d->cam.cos);
	new.x /= new.z;
	new.y /= new.z;
	new.x = new.x * WIDTH + WIDTH * 0.5;
	new.y = new.y * -WIDTH + HEIGHT * 0.5 - d->cam.y_offset;
	return (new);
}

void		display_proj(t_env *d, t_frustum *fr, t_anim_rot proj)
{
	double			dist;
	t_display_data	a;
	t_vec3f			point_on_screen;

	point_on_screen = v3f_transpar(d, proj.pos);
	if (point_on_screen.z <= 0)
		return ;
	dist = vec3f_length(v3_min(proj.pos, d->cam.pos));
	a.start.x = point_on_screen.x - (d->anim_rot_text[proj.weapon_id]
			[proj.is_curr_anim]->w *
			d->anim_rot_type[proj.id_type].size) / dist;
	a.end.x = point_on_screen.x + (d->anim_rot_text[proj.weapon_id]
			[proj.is_curr_anim]->w *
			d->anim_rot_type[proj.id_type].size) / dist;
	a.start.y = point_on_screen.y - (d->anim_rot_text[proj.weapon_id]
			[proj.is_curr_anim]->h *
			d->anim_rot_type[proj.id_type].size) / dist;
	a.end.y = point_on_screen.y + (d->anim_rot_text[proj.weapon_id]
			[proj.is_curr_anim]->h *
			d->anim_rot_type[proj.id_type].size) / dist;
	replace_data_to_disp(fr, &a, proj.this_sect);
	displaing_sprite(d, d->anim_rot_text[proj.id_type]
			[proj.is_curr_anim], a, new_v2(point_on_screen.z, 2));
}
