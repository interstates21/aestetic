/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:33:06 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 16:33:07 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void		pt4(t_env *d, t_font f, char c)
{
	if (c == '3')
		draw_bitmap(d, d->chars.n3, f.x, f.y);
	else if (c == '4')
		draw_bitmap(d, d->chars.n4, f.x, f.y);
	else if (c == '5')
		draw_bitmap(d, d->chars.n5, f.x, f.y);
	else if (c == '6')
		draw_bitmap(d, d->chars.n6, f.x, f.y);
	else if (c == '7')
		draw_bitmap(d, d->chars.n7, f.x, f.y);
	else if (c == '8')
		draw_bitmap(d, d->chars.n8, f.x, f.y);
	else if (c == '9')
		draw_bitmap(d, d->chars.n9, f.x, f.y);
	else if (c == ':')
		draw_bitmap(d, d->chars.semi, f.x, f.y);
	else if (c == '/')
		draw_bitmap(d, d->chars.slh, f.x, f.y);
	else if (c == '%')
		draw_bitmap(d, d->chars.prc, f.x, f.y);
	else
		draw_bitmap(d, d->chars.spc, f.x, f.y);
}

static void		pt3(t_env *d, t_font f, char c)
{
	if (c == 'V')
		draw_bitmap(d, d->chars.v, f.x, f.y);
	else if (c == 'U')
		draw_bitmap(d, d->chars.u, f.x, f.y);
	else if (c == 'W')
		draw_bitmap(d, d->chars.w, f.x, f.y);
	else if (c == 'X')
		draw_bitmap(d, d->chars.x, f.x, f.y);
	else if (c == 'Y')
		draw_bitmap(d, d->chars.y, f.x, f.y);
	else if (c == 'Z')
		draw_bitmap(d, d->chars.z, f.x, f.y);
	else if (c == '.')
		draw_bitmap(d, d->chars.dot, f.x, f.y);
	else if (c == '!')
		draw_bitmap(d, d->chars.exc, f.x, f.y);
	else if (c == '0')
		draw_bitmap(d, d->chars.n0, f.x, f.y);
	else if (c == '1')
		draw_bitmap(d, d->chars.n1, f.x, f.y);
	else if (c == '2')
		draw_bitmap(d, d->chars.n2, f.x, f.y);
	else
		pt4(d, f, c);
}

static void		pt2(t_env *d, t_font f, char c)
{
	if (c == 'J')
		draw_bitmap(d, d->chars.j, f.x, f.y);
	else if (c == 'K')
		draw_bitmap(d, d->chars.k, f.x, f.y);
	else if (c == 'L')
		draw_bitmap(d, d->chars.l, f.x, f.y);
	else if (c == 'M')
		draw_bitmap(d, d->chars.m, f.x, f.y);
	else if (c == 'N')
		draw_bitmap(d, d->chars.n, f.x, f.y);
	else if (c == 'O')
		draw_bitmap(d, d->chars.o, f.x, f.y);
	else if (c == 'P')
		draw_bitmap(d, d->chars.p, f.x, f.y);
	else if (c == 'Q')
		draw_bitmap(d, d->chars.q, f.x, f.y);
	else if (c == 'R')
		draw_bitmap(d, d->chars.r, f.x, f.y);
	else if (c == 'S')
		draw_bitmap(d, d->chars.s, f.x, f.y);
	else if (c == 'T')
		draw_bitmap(d, d->chars.t, f.x, f.y);
	else
		pt3(d, f, c);
}

void			draw_char(t_env *d, t_font f)
{
	char c;

	c = ft_toupper(*f.str);
	if (c == 'A')
		draw_bitmap(d, d->chars.a, f.x, f.y);
	else if (c == 'B')
		draw_bitmap(d, d->chars.b, f.x, f.y);
	else if (c == 'C')
		draw_bitmap(d, d->chars.c, f.x, f.y);
	else if (c == 'D')
		draw_bitmap(d, d->chars.d, f.x, f.y);
	else if (c == 'E')
		draw_bitmap(d, d->chars.e, f.x, f.y);
	else if (c == 'F')
		draw_bitmap(d, d->chars.f, f.x, f.y);
	else if (c == 'G')
		draw_bitmap(d, d->chars.g, f.x, f.y);
	else if (c == 'H')
		draw_bitmap(d, d->chars.h, f.x, f.y);
	else if (c == 'I')
		draw_bitmap(d, d->chars.i, f.x, f.y);
	else
		pt2(d, f, c);
}
