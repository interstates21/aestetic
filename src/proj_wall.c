/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:12:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:04:09 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

//not_refact

void	*draw_ceil_thread(void *void_arg)
{
	t_thread_arg	*arg;

	arg = (t_thread_arg*)void_arg;
	if (!arg->p->sector->outdoor)
		displaing_cl_fl(arg->d, arg->p, arg->fr, 0);
	else
		displaing_sky(arg->d, arg->p, arg->fr);
	return (NULL);
}

void	proj_wall2(t_env *d, t_projdata *p, t_frustum *fr)
{
	pthread_t		thread;
	t_thread_arg	t;

	if (p->wall->posterpicnum >= 0)
	{
		p->u1_poster = (p->len - POSTER_W) / 2.0;
		p->u2_poster = p->len - p->u1_poster;
		p->poster_h = POSTER_W * ((double)d->posters[p->wall->posterpicnum]->h /
				d->posters[p->wall->posterpicnum]->w) / p->y_scale;
	}
	displaing_wall(d, p, fr);
	t = (t_thread_arg){d, p, fr};
	if (pthread_create(&thread, NULL, draw_ceil_thread, &t))
		print_err("thread error");
	displaing_cl_fl(d, p, fr, 1);
	if (pthread_join(thread, NULL))
		print_err("thread error");
}

void	proj_wall(t_env *d, t_projdata *p, t_frustum *fr, t_vec2f v[2])
{
	double offset;

	p->scale1 = (1.0 / p->z1) * WIDTH;
	p->scale2 = (1.0 / p->z2) * WIDTH;
	p->x1 = p->x1 * p->scale1 + WIDTH / 2;
	p->x2 = p->x2 * p->scale2 + WIDTH / 2;
	offset = HEIGHT / 2 - d->cam.y_offset;
	p->y1a = cl_calc_vec_cal(d, p->sector, v[0]) * -p->scale1 + offset;
	p->y2a = cl_calc_vec_cal(d, p->sector, v[1]) * -p->scale2 + offset;
	p->y1b = fl_calc_vec_cal(d, p->sector, v[0]) * -p->scale1 + offset;
	p->y2b = fl_calc_vec_cal(d, p->sector, v[1]) * -p->scale2 + offset;
	p->y1c = (p->sector->ceilheight - d->cam.pos.y) * -p->scale1 + offset;
	p->y2c = (p->sector->ceilheight - d->cam.pos.y) * -p->scale2 + offset;
	p->y1d = (p->sector->floorheight - d->cam.pos.y) * -p->scale1 + offset;
	p->y2d = (p->sector->floorheight - d->cam.pos.y) * -p->scale2 + offset;
	p->y_scale = p->sector->ceilheight - p->sector->floorheight;
	if (p->neighbor)
	{
		p->ny1a = cl_calc_vec_cal(d, p->neighbor, v[0]) * -p->scale1 + offset;
		p->ny2a = cl_calc_vec_cal(d, p->neighbor, v[1]) * -p->scale2 + offset;
		p->ny1b = fl_calc_vec_cal(d, p->neighbor, v[0]) * -p->scale1 + offset;
		p->ny2b = fl_calc_vec_cal(d, p->neighbor, v[1]) * -p->scale2 + offset;
	}
	proj_wall2(d, p, fr);
}
