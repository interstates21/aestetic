/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:21:44 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 14:36:21 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	invoke_msg(t_data *d, char *msg)
{
	if (ft_strlen(msg) > 99)
		return ((void)printf("msg is too long\n"));
	ft_strcpy(d->msg, msg);
	d->msg_start = SDL_GetTicks();
}

double	get_dist(t_vec2f a, t_vec2f b, t_vec2f p)
{
	return (v2_len(v2_min(p, get_closest(a, b, p))));
}

void	whi_le(t_data *d, t_sector *sect, int *n, double *m)
{
	while (n[3] < sect->firstwallnum + sect->numwalls)
	{
		if (d->walls[n[2]].is_door && d->walls[n[2]].neighborsect >= 0 &&
				(m[0] = get_dist(d->walls[n[2]].point, d->walls[n[3]].point,
				v3_to_v2(d->cam.pos))) < ACTIVATION_DIST && m[0] < m[1] &&
					(m[1] = m[0]) >= 0 &&
					(n[0] = n[2]) >= 0)
			n[1] = n[3];
		n[2] = n[3]++;
	}
}

void	change_buf_colo(t_data *d, uint16_t amount, uint32_t colo)
{
	if (d->color_buf.colo != colo)
	{
		d->color_buf.value = 0;
		d->color_buf.colo = colo;
	}
	d->color_buf.value += amount * 18;
	if (d->color_buf.value > MAX_BUF_VALUE)
		d->color_buf.value = MAX_BUF_VALUE;
}

void	alpha_y(double *sl_y)
{
	short y;

	y = -1;
	while (++y < HEIGHT)
		sl_y[y] = fabs(y - HEIGHT * 0.5) / (HEIGHT * 0.5);
}