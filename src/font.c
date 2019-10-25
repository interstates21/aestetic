/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:18:24 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/25 21:52:29 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

//norminette

void	init_font(t_data *d)
{
	*d = (t_data){.chars.a.bit = {0x7e, 0xff, 0xe7, 0xe7, 0xff,
															0xff, 0xe7, 0xe7},
	.chars.b.bit = {0xfe, 0xff, 0xe7, 0xfe, 0xfe, 0xe7, 0xff, 0xfe},
	.chars.c.bit = {0x7e, 0xff, 0xe7, 0xe0, 0xe0, 0xe7, 0xff, 0x7e},
	.chars.d.bit = {0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xfe},
	.chars.e.bit = {0xff, 0xff, 0xe0, 0xfc, 0xfc, 0xe0, 0xff, 0xff},
	.chars.f.bit = {0xff, 0xff, 0xe0, 0xfc, 0xfc, 0xe0, 0xe0, 0xe0},
	.chars.g.bit = {0x7e, 0xff, 0xe7, 0xe0, 0xef, 0xe7, 0xff, 0x7e},
	.chars.h.bit = {0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xe7},
	.chars.i.bit = {0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c},
	.chars.j.bit = {0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xfc, 0xf8},
	.chars.k.bit = {0xe3, 0xe7, 0xee, 0xfc, 0xfc, 0xee, 0xe7, 0xe3},
	.chars.l.bit = {0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff},
	.chars.m.bit = {0xc3, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7},
	.chars.n.bit = {0xe7, 0xf7, 0xf7, 0xff, 0xff, 0xff, 0xef, 0xe7},
	.chars.o.bit = {0x7e, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7e},
	.chars.p.bit = {0xfe, 0xff, 0xe7, 0xff, 0xfe, 0xe0, 0xe0, 0xe0},
	.chars.q.bit = {0x7e, 0xff, 0xc7, 0xc7, 0xc3, 0xd9, 0xec, 0x63},
	.chars.r.bit = {0xfe, 0xff, 0xe7, 0xff, 0xfe, 0xe7, 0xe7, 0xe7},
	.chars.s.bit = {0x7e, 0xff, 0xe0, 0xfe, 0x7f, 0x07, 0xff, 0x7e},
	.chars.t.bit = {0xfe, 0xfe, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38},
	.chars.u.bit = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7e},
	.chars.v.bit = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7e, 0x3c},
	.chars.w.bit = {0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xff, 0x7e, 0xaa},
	.chars.x.bit = {0xe7, 0xe7, 0x7e, 0x3c, 0x3c, 0x7e, 0xe7, 0xe8},
	.chars.y.bit = {0xe7, 0xe7, 0xe7, 0x7e, 0x3c, 0x18, 0x18, 0x18},
	.chars.z.bit = {0xe7, 0xf7, 0xf7, 0xff, 0xff, 0xff, 0xef, 0xe7},
	.chars.dot.bit = {0, 0, 0, 0, 0, 0, 0x18, 0x18},
	.chars.spc.bit = {0, 0, 0, 0, 0, 0, 0},
	.chars.semi.bit = {0, 0x18, 0x18, 0, 0, 0x18, 0x18, 0},
	.chars.n0.bit = {0x7e, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7e},
	.chars.n1.bit = {0x38, 0x78, 0xf8, 0x38, 0x38, 0x38, 0x38, 0x38},
	.chars.n2.bit = {0x7e, 0xff, 0xe7, 0x0e, 0x38, 0xe0, 0xff, 0xff},
	.chars.n3.bit = {0xfe, 0xff, 0x07, 0xfe, 0xfe, 0x07, 0xff, 0xfe},
	.chars.n4.bit = {0xee, 0xee, 0xee, 0xff, 0xff, 0x0e, 0x0e, 0x0e},
	.chars.n5.bit = {0xff, 0xff, 0xe0, 0xfe, 0xff, 0x07, 0xff, 0x7e},
	.chars.n6.bit = {0x7e, 0xff, 0xe0, 0xfe, 0xff, 0xe7, 0xff, 0x7e},
	.chars.n7.bit = {0xff, 0xff, 0x07, 0x0e, 0x1c, 0x38, 0x38, 0x38},
	.chars.n8.bit = {0x7e, 0xff, 0xe7, 0x7e, 0x7e, 0xe7, 0xff, 0x7e},
	.chars.n9.bit = {0x7e, 0xff, 0xe7, 0xff, 0x7f, 0x07, 0xff, 0x7e},
	.chars.slh.bit = {0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
	.chars.prc.bit = {0x66, 0x66, 0x0c, 0x0c, 0x18, 0x18, 0x33, 0x33},
	.chars.exc.bit = {0x18, 0x18, 0x18, 0x18, 0, 0x18}};
}

void	draw_bitmap(t_data *d, t_bitmap bitmap, int x, int y)
{
	int		i;
	int		j;

	j = -1;
	while (++j < 8)
	{
		i = -1;
		while (++i < 9)
		{
			if ((bitmap.bit[j] >> (8 - i)) & 1)
			{
				putpixel(d, x + i, y + j, 0xffffff);
			}
		}
	}
}

void	draw_char(t_data *d, char *str, int x, int y)
{
	char c;

	c = ft_toupper(*str);
	if (c == 'A')
		draw_bitmap(d, d->chars.a, x, y);
	else if (c == 'B')
		draw_bitmap(d, d->chars.b, x, y);
	else if (c == 'C')
		draw_bitmap(d, d->chars.c, x, y);
	else if (c == 'D')
		draw_bitmap(d, d->chars.d, x, y);
	else if (c == 'E')
		draw_bitmap(d, d->chars.e, x, y);
	else if (c == 'F')
		draw_bitmap(d, d->chars.f, x, y);
	else if (c == 'G')
		draw_bitmap(d, d->chars.g, x, y);
	else if (c == 'H')
		draw_bitmap(d, d->chars.h, x, y);
	else if (c == 'I')
		draw_bitmap(d, d->chars.i, x, y);
	else if (c == 'J')
		draw_bitmap(d, d->chars.j, x, y);
	else if (c == 'K')
		draw_bitmap(d, d->chars.k, x, y);
	else if (c == 'L')
		draw_bitmap(d, d->chars.l, x, y);
	else if (c == 'M')
		draw_bitmap(d, d->chars.m, x, y);
	else if (c == 'N')
		draw_bitmap(d, d->chars.n, x, y);
	else if (c == 'O')
		draw_bitmap(d, d->chars.o, x, y);
	else if (c == 'P')
		draw_bitmap(d, d->chars.p, x, y);
	else if (c == 'Q')
		draw_bitmap(d, d->chars.q, x, y);
	else if (c == 'R')
		draw_bitmap(d, d->chars.r, x, y);
	else if (c == 'S')
		draw_bitmap(d, d->chars.s, x, y);
	else if (c == 'T')
		draw_bitmap(d, d->chars.t, x, y);
	else if (c == 'U')
		draw_bitmap(d, d->chars.u, x, y);
	else if (c == 'V')
		draw_bitmap(d, d->chars.v, x, y);
	else if (c == 'W')
		draw_bitmap(d, d->chars.w, x, y);
	else if (c == 'X')
		draw_bitmap(d, d->chars.x, x, y);
	else if (c == 'Y')
		draw_bitmap(d, d->chars.y, x, y);
	else if (c == 'Z')
		draw_bitmap(d, d->chars.z, x, y);
	else if (c == '.')
		draw_bitmap(d, d->chars.dot, x, y);
	else if (c == '!')
		draw_bitmap(d, d->chars.exc, x, y);
	else if (c == '0')
		draw_bitmap(d, d->chars.n0, x, y);
	else if (c == '1')
		draw_bitmap(d, d->chars.n1, x, y);
	else if (c == '2')
		draw_bitmap(d, d->chars.n2, x, y);
	else if (c == '3')
		draw_bitmap(d, d->chars.n3, x, y);
	else if (c == '4')
		draw_bitmap(d, d->chars.n4, x, y);
	else if (c == '5')
		draw_bitmap(d, d->chars.n5, x, y);
	else if (c == '6')
		draw_bitmap(d, d->chars.n6, x, y);
	else if (c == '7')
		draw_bitmap(d, d->chars.n7, x, y);
	else if (c == '8')
		draw_bitmap(d, d->chars.n8, x, y);
	else if (c == '9')
		draw_bitmap(d, d->chars.n9, x, y);
	else if (c == ':')
		draw_bitmap(d, d->chars.semi, x, y);
	else if (c == '/')
		draw_bitmap(d, d->chars.slh, x, y);
	else if (c == '%')
		draw_bitmap(d, d->chars.prc, x, y);
	else
		draw_bitmap(d, d->chars.spc, x, y);
}

void	draw_string(t_data *d, t_font f)
{
	int			x_start;

	x_start = f.x;
	while (*f.str)
	{
		draw_char(d, f.str, f.x, f.y);
		f.x += 10;
		f.str++;
		if (*f.str == '\n' && ((f.x = x_start) == x_start) && f.str++)
			f.y += (CHAR_HEIGHT + 10) * f.scale;
	}
}
