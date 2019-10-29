/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:29:56 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:10:50 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	actualize_dir(double diff, t_vec2f *dir)
{
	double	x;
	double	y;

	x = dir->x;
	y = dir->y;
	dir->x = x * cos(diff) - y * sin(diff);
	dir->y = x * sin(diff) + y * cos(diff);
}

bool	is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point)
{
	if ((point.x < p1.x && point.x < p2.x) ||
			(point.x > p1.x && point.x > p2.x))
		return (false);
	if ((point.y < p1.y && point.y < p2.y) ||
			(point.y > p1.y && point.y > p2.y))
		return (false);
	return (true);
}

void	print_v(t_vec2 v, const char *s)
{
	ft_putstr(s);
	ft_putstr(" -- x: ");
	ft_putnbr(v.x);
	ft_putstr(" y: ");
	ft_putnbr(v.y);
	ft_putchar('\n');
}
