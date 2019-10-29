/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 23:03:43 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:41:33 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	replace_data_to_disp(t_frustum *fr, t_display_data *disp_data,
		uint16_t this_sect)
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
	disp_data->this_sect = this_sect;
}

void	replace_data_to_disp_1(t_display_data *disp_data,
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

void	replace_data_to_disp_2(t_display_data *disp_data,
		uint16_t this_sect)
{
	double large_x;
	double large_y;

	large_x = disp_data->start.x - disp_data->end.x;
	large_y = disp_data->start.y - disp_data->end.y;
	disp_data->scale.x = fabs(100.0 / large_x * 0.01);
	disp_data->cut_start = MAX(disp_data->start.x, 0);
	disp_data->cut_end = MIN(disp_data->end.x, WIDTH - 1);
	disp_data->scale.y = fabs(100.0 / large_y * 0.01);
	disp_data->this_sect = this_sect;
}
