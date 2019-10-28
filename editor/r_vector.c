/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:45:09 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:45:09 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_v2	new_v2(int a, int b)
{
	t_v2 v;

	v.x = a;
	v.y = b;
	return (v);
}

int		wall_eq(t_wall a, t_wall b)
{
	return ((a.v1.x == b.v1.x &&
	a.v1.y == b.v1.y &&
	a.v2.x == b.v2.x &&
	a.v2.y == b.v2.y) ||
	(a.v2.x == b.v1.x &&
	a.v2.y == b.v1.y &&
	a.v1.x == b.v2.x &&
	a.v1.y == b.v2.y));
}

int		v2_cmp(t_v2 a, t_v2 b)
{
	return (a.x == b.x && a.y == b.y);
}

t_bool	v2_compare(t_v2 a, t_v2 b, int r)
{
	if (a.y - r <= b.y && a.y + r >= b.y)
		if (a.x - r <= b.x && a.x + r >= b.x)
			return (true);
	return (false);
}
