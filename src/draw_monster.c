/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:45:21 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/26 21:42:32 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	new_disp_data_1(t_display_data *disp_data,
		SDL_Surface *s, t_vec3f p_in_scr, double size)
{
	double	start_x;
	double	start_y;

	start_x = (s->w) / p_in_scr.z * size;
	start_y = (s->h * 2) / p_in_scr.z * size;
	disp_data->start.x = p_in_scr.x - start_x;
	disp_data->end.x = p_in_scr.x + start_x;
	disp_data->start.y = p_in_scr.y - start_y;
	disp_data->end.y = p_in_scr.y;
}

static void	new_disp_data_2(t_display_data *disp_data,
		uint16_t cursectnum)
{
	double large_x;
	double large_y;

	large_x = disp_data->start.x - disp_data->end.x;
	large_y = disp_data->start.y - disp_data->end.y;
	disp_data->scale.x = fabs(100.0 / large_x * 0.01);
	disp_data->cut_start = MAX(disp_data->start.x, 0);
	disp_data->cut_end = MIN(disp_data->end.x, WIDTH - 1);
	disp_data->scale.y = fabs(100.0 / large_y * 0.01);
	disp_data->cursectnum = cursectnum;
}

short		*mont_anim(t_data *d, t_monster monster, short *nb_of_anim)
{
	nb_of_anim[1] = get_nb_anim_from_rotation(monster.rot,
			monster.pos, v3_to_v2(d->cam.pos));
	nb_of_anim[0] = nb_of_anim[1];
	if (nb_of_anim[1] > 4)
		nb_of_anim[0] = 8 - nb_of_anim[0];
	return (nb_of_anim);
}

void		new_zbuffer_and_put_collor(t_data *d, t_vec2 x_y, uint32_t colo,
															t_vec2f dist_mod)
{
	pixel_put(d, (t_vec3f){x_y.x, x_y.y, 0}, colo, 0);
	d->zbuffer[x_y.x + x_y.y * d->sdl.screen->w] = dist_mod.x;
}

void		draw_monster(t_data *d, t_monster monster)
{
	t_display_data	a;
	t_vec3f			point_in_screen;
	t_vec3f			position_monstr;
	double			h;
	short			nb_of_anim[2];

	h = get_floor_height(&d->sectors[monster.cursectnum], d->walls,
									monster.cursectnum, monster.pos);
	position_monstr = new_v3(monster.pos.x, h, monster.pos.y);
	point_in_screen = trans_v3f_in_scr(d, position_monstr);
	if (point_in_screen.z <= 0)
		return ;
	nb_of_anim[0] = *mont_anim(d, monster, nb_of_anim);
	new_disp_data_1(&a, d->monster_text[monster.id_type][monster.
			anim_state][nb_of_anim[0]], point_in_screen,
			d->monster_type[monster.id_type].size);
	new_disp_data_2(&a, monster.cursectnum);
	if (nb_of_anim[1] < 4 && monster.anim_state < 10)
		disp_sprite(d, d->monster_text[monster.id_type]
	[monster.anim_state][nb_of_anim[0]], a, (t_vec2f){point_in_screen.z, 0});
	else
		disp_sprite(d, d->monster_text[monster.id_type]
	[monster.anim_state][nb_of_anim[0]], a, (t_vec2f){point_in_screen.z, 1});
}
