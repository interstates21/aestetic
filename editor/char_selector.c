/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:55 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 17:44:56 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		pt4(t_ed *d, t_font f, char c)
{
	if (c == '3')
		draw_bitmap(d, d->chars.n3, f);
	else if (c == '4')
		draw_bitmap(d, d->chars.n4, f);
	else if (c == '5')
		draw_bitmap(d, d->chars.n5, f);
	else if (c == '6')
		draw_bitmap(d, d->chars.n6, f);
	else if (c == '7')
		draw_bitmap(d, d->chars.n7, f);
	else if (c == '8')
		draw_bitmap(d, d->chars.n8, f);
	else if (c == '9')
		draw_bitmap(d, d->chars.n9, f);
	else if (c == ':')
		draw_bitmap(d, d->chars.semi, f);
	else if (c == '/')
		draw_bitmap(d, d->chars.slh, f);
	else if (c == '%')
		draw_bitmap(d, d->chars.prc, f);
	else
		draw_bitmap(d, d->chars.spc, f);
}

static void		pt3(t_ed *d, t_font f, char c)
{
	if (c == 'V')
		draw_bitmap(d, d->chars.v, f);
	else if (c == 'U')
		draw_bitmap(d, d->chars.u, f);
	else if (c == 'W')
		draw_bitmap(d, d->chars.w, f);
	else if (c == 'X')
		draw_bitmap(d, d->chars.x, f);
	else if (c == 'Y')
		draw_bitmap(d, d->chars.y, f);
	else if (c == 'Z')
		draw_bitmap(d, d->chars.z, f);
	else if (c == '.')
		draw_bitmap(d, d->chars.dot, f);
	else if (c == '!')
		draw_bitmap(d, d->chars.exc, f);
	else if (c == '0')
		draw_bitmap(d, d->chars.n0, f);
	else if (c == '1')
		draw_bitmap(d, d->chars.n1, f);
	else if (c == '2')
		draw_bitmap(d, d->chars.n2, f);
	else
		pt4(d, f, c);
}

static void		pt2(t_ed *d, t_font f, char c)
{
	if (c == 'J')
		draw_bitmap(d, d->chars.j, f);
	else if (c == 'K')
		draw_bitmap(d, d->chars.k, f);
	else if (c == 'L')
		draw_bitmap(d, d->chars.l, f);
	else if (c == 'M')
		draw_bitmap(d, d->chars.m, f);
	else if (c == 'N')
		draw_bitmap(d, d->chars.n, f);
	else if (c == 'O')
		draw_bitmap(d, d->chars.o, f);
	else if (c == 'P')
		draw_bitmap(d, d->chars.p, f);
	else if (c == 'Q')
		draw_bitmap(d, d->chars.q, f);
	else if (c == 'R')
		draw_bitmap(d, d->chars.r, f);
	else if (c == 'S')
		draw_bitmap(d, d->chars.s, f);
	else if (c == 'T')
		draw_bitmap(d, d->chars.t, f);
	else
		pt3(d, f, c);
}

void			draw_char(t_ed *d, t_font f)
{
	char c;

	c = ft_toupper(*f.str);
	if (c == 'A')
		draw_bitmap(d, d->chars.a, f);
	else if (c == 'B')
		draw_bitmap(d, d->chars.b, f);
	else if (c == 'C')
		draw_bitmap(d, d->chars.c, f);
	else if (c == 'D')
		draw_bitmap(d, d->chars.d, f);
	else if (c == 'E')
		draw_bitmap(d, d->chars.e, f);
	else if (c == 'F')
		draw_bitmap(d, d->chars.f, f);
	else if (c == 'G')
		draw_bitmap(d, d->chars.g, f);
	else if (c == 'H')
		draw_bitmap(d, d->chars.h, f);
	else if (c == 'I')
		draw_bitmap(d, d->chars.i, f);
	else
		pt2(d, f, c);
}
