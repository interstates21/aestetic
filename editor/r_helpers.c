/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:31:26 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:31:29 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_v2		trim_v2(t_v2 v)
{
	t_v2	res;
	int		sign;

	sign = v.x % GRID_GAP > GRID_GAP >> 1 ? 1 : -1;
	res.x = trim(v.x, sign);
	sign = v.y % GRID_GAP > GRID_GAP >> 1 ? 1 : -1;
	res.y = trim(v.y, sign);
	return (res);
}

int			trim(int v, int inc)
{
	while (v % GRID_GAP)
		v += inc;
	return (v);
}

void		print_err(const char *err)
{
	ft_putstr("Init Error = ");
	ft_putendl(err);
	exit(1);
}
