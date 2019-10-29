/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_monster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:45:21 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:42:40 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

short		*mont_anim(t_env *d, t_monster monster, short *nb_of_anim)
{
	nb_of_anim[1] = get_nb_anim_from_rotation(monster.rot,
			monster.pos, v3_to_v2(d->cam.pos));
	nb_of_anim[0] = nb_of_anim[1];
	if (nb_of_anim[1] > 4)
		nb_of_anim[0] = 8 - nb_of_anim[0];
	return (nb_of_anim);
}

void		display_monster(t_env *d, t_monster monster)
{
	t_display_data	a;
	t_vec3f			point_in_screen;
	t_vec3f			position_monstr;
	double			h;
	short			nb_of_anim[2];

	h = height_fl_val(&d->sectors[monster.this_sect], d->walls,
									monster.this_sect, monster.pos);
	position_monstr = new_v3(monster.pos.x, h, monster.pos.y);
	point_in_screen = v3f_transpar(d, position_monstr);
	if (point_in_screen.z <= 0)
		return ;
	nb_of_anim[0] = *mont_anim(d, monster, nb_of_anim);
	replace_data_to_disp_1(&a, d->monster_text[monster.id_type][monster.
			anim_state][nb_of_anim[0]], point_in_screen,
			d->monster_type[monster.id_type].size);
	replace_data_to_disp_2(&a, monster.this_sect);
	if (nb_of_anim[1] < 4 && monster.anim_state < 10)
		displaing_sprite(d, d->monster_text[monster.id_type]
	[monster.anim_state][nb_of_anim[0]], a, new_v2(point_in_screen.z, 0));
	else
		displaing_sprite(d, d->monster_text[monster.id_type]
	[monster.anim_state][nb_of_anim[0]], a, new_v2(point_in_screen.z, 1));
}
