/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:54:20 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 13:22:26 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void set_1(t_vec2f p0, t_vec2f p1, double *arr)
{
	arr[0] = p1.y - p0.y;
	arr[2] = p0.x - p1.x;
	arr[4] = arr[0] * p0.x + arr[2] * p0.y;
}

static void set_2(t_vec2f p2, t_vec2f p3, double *arr)
{
	arr[1] = p3.y - p2.y;
	arr[3] = p2.x - p3.x;
	arr[5] = arr[1] * p2.x + arr[3] * p2.y;
}

t_vec2f		intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2, t_vec2f p3)
{
	double	arr[6];
	double	broz;

	set_1(p0, p1, arr);
	set_2(p2, p3, arr);
	broz = arr[0] * arr[3] - arr[1] * arr[2];
	if (broz == 0)
		return ((t_vec2f){-1, -1});
	return ((t_vec2f){(arr[3] * arr[4] - arr[2] * arr[5]) / broz,
			(arr[0] * arr[5] - arr[1] * arr[4]) / broz});
}

bool		clip_wall(double *x1, double *z1, double x2, double z2)
{
	t_vec2f	p0;
	t_vec2f p1;
	t_vec2f pAll;
	double	rez;

	p0 = (t_vec2f){*x1, *z1};
	p1 = (t_vec2f){x2, z2};
	rez = (LERP(NORMALIZE(0, p0.y, p1.y), p0.x, p1.x) < 0) ? -1 : 1;
	pAll = intersect(p0, p1, (t_vec2f){((rez * WIDTH / 2.0) / WIDTH) *
			1.0, 1}, (t_vec2f){((rez * WIDTH / 2.0) / WIDTH) * 10.0, 10});
	if (pAll.y <= 0)
		return (false);
	if (((p0.x - p1.x) < 0) != ((pAll.x - p1.x) < 0))
		return (false);
	*x1 = pAll.x;
	*z1 = pAll.y;
	return (true);
}
