/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:21:13 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:08:31 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_range	make_range(int min, int max)
{
	t_range r;

	r.min = min;
	r.max = max;
	r.t = 0;
	return (r);
}

t_range	add_range(t_range a, t_range b)
{
	t_range r;

	r.min = a.min + b.min;
	r.max = a.max + b.max;
	r.t = 0;
	return (r);
}

t_range	minus_range(t_range a, t_range b)
{
	t_range r;

	r.min = a.min - b.min;
	r.max = a.max - b.max;
	r.t = 0;
	return (r);
}

t_range	mult_range(t_range a, t_range b)
{
	t_range r;

	r.min = a.min * b.min;
	r.max = a.max * b.max;
	r.t = 0;
	return (r);
}

t_range	div_range(t_range a, t_range b)
{
	t_range r;

	if (b.min == 0 || b.max == 0)
		return (make_range(0, 0));
	r.min = a.min / b.min;
	r.max = a.max / b.max;
	r.t = 0;
	return (r);
}
