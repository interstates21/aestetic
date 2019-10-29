/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:21:13 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:57:09 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

t_range	ranged_create(int min, int max)
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
		return (ranged_create(0, 0));
	r.min = a.min / b.min;
	r.max = a.max / b.max;
	r.t = 0;
	return (r);
}
