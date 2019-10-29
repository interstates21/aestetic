/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:21:44 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 22:06:25 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	massege_print(t_env *d, char *msg)
{
	ft_strcpy(d->msg, msg);
	d->msg_start = SDL_GetTicks();
}

double	distanse_place(t_vec2f a, t_vec2f b, t_vec2f p)
{
	return (v2_len(v2_min(p, to_close_val(a, b, p))));
}

void	door_func(t_env *d, t_sec *sect, int *n, double *m)
{
	while (n[3] < sect->firstwallnum + sect->n_walls)
	{
		if (d->walls[n[2]].is_door && d->walls[n[2]].neighborsect >= 0 &&
				(m[0] = distanse_place(d->walls[n[2]].point, d->
														walls[n[3]].point,
				v3_to_v2(d->cam.pos))) < ACTIVATION_DIST && m[0] < m[1] &&
					(m[1] = m[0]) >= 0 &&
					(n[0] = n[2]) >= 0)
			n[1] = n[3];
		n[2] = n[3]++;
	}
}

void	buf_to_collor2(t_env *d, uint16_t amount, uint32_t colo)
{
	if (d->pxls.colo != colo)
	{
		d->pxls.value = 0;
		d->pxls.colo = colo;
	}
	d->pxls.value += amount * 18;
	if (d->pxls.value > MAX_BUF_VALUE)
		d->pxls.value = MAX_BUF_VALUE;
}

void	alpha_serch(double *sl_y)
{
	short y;

	y = 0;
	while (y < HEIGHT)
	{
		sl_y[y] = fabs(y - (double)(HEIGHT >> 1)) / (double)((HEIGHT >> 1));
		y++;
	}
}
