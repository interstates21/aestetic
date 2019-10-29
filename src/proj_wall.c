/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:12:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:57:38 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

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

void	proj_wall3(t_env *d, t_proj_env *p, t_frustum *fr)
{
	p->u1_poster = (p->len - POSTER_W) / 2.0;
	p->u2_poster = p->len - p->u1_poster;
	p->poster_h = POSTER_W * ((double)d->posters[p->wall->posterpicnum]->h /
		d->posters[p->wall->posterpicnum]->w) / p->y_scale;
}

void	proj_wall2(t_env *d, t_proj_env *p, t_frustum *fr)
{
	pthread_t		oprs;
	t_thread_arg	t;

	if (p->wall->posterpicnum >= 0)
		proj_wall3(d, p, fr);
	displaing_wall(d, p, fr);
	t = (t_thread_arg){d, p, fr};
	if (pthread_create(&oprs, NULL, draw_ceil_thread, &t))
		print_err("thread error");
	displaing_cl_fl(d, p, fr, 1);
	if (pthread_join(oprs, NULL))
		print_err("thread error");
}

void	wal4(t_proj_env *p, t_vec2f *v)
{
	p->scale1 = (1.0 / p->z1) * WIDTH;
	p->scale2 = (1.0 / p->z2) * WIDTH;
	p->x1 = p->x1 * p->scale1 + WIDTH / 2;
	p->x2 = p->x2 * p->scale2 + WIDTH / 2;
}

void	proj_wall(t_env *d, t_proj_env *z, t_frustum *fr, t_vec2f v[2])
{
	double wouset;

	wal4(z, v);
	wouset = HEIGHT / 2 - d->cam.y_offset;
	z->y1a = cl_calc_vec_cal(d, z->sector, v[0]) * -z->scale1 + wouset;
	z->y2a = cl_calc_vec_cal(d, z->sector, v[1]) * -z->scale2 + wouset;
	z->y1b = fl_calc_vec_cal(d, z->sector, v[0]) * -z->scale1 + wouset;
	z->y2b = fl_calc_vec_cal(d, z->sector, v[1]) * -z->scale2 + wouset;
	z->y1c = (z->sector->ceilheight - d->cam.pos.y) * -z->scale1 + wouset;
	z->y2c = (z->sector->ceilheight - d->cam.pos.y) * -z->scale2 + wouset;
	z->y1d = (z->sector->floorheight - d->cam.pos.y) * -z->scale1 + wouset;
	z->y2d = (z->sector->floorheight - d->cam.pos.y) * -z->scale2 + wouset;
	z->y_scale = z->sector->ceilheight - z->sector->floorheight;
	if (z->portal)
	{
		z->ny1a = cl_calc_vec_cal(d, z->portal, v[0]) * -z->scale1 + wouset;
		z->ny2a = cl_calc_vec_cal(d, z->portal, v[1]) * -z->scale2 + wouset;
		z->ny1b = fl_calc_vec_cal(d, z->portal, v[0]) * -z->scale1 + wouset;
		z->ny2b = fl_calc_vec_cal(d, z->portal, v[1]) * -z->scale2 + wouset;
	}
	proj_wall2(d, z, fr);
}
