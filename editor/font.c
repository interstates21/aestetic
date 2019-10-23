#include "../includes/editor.h"

static void	s(int arr[8], t_bitmap *b)
{
	int 	i;

	i = -1;
	while (++i < 8)
		b->bit[i] = arr[i];
}

static void	part_w(t_ed *d)
{
	s((int[8]){0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7e, 0x3c}, &d->chars.v);
	s((int[8]){0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xff, 0x7e, 0x66}, &d->chars.w);
	s((int[8]){0xe7, 0xe7, 0x7e, 0x3c, 0x3c, 0x7e, 0xe7, 0xe7}, &d->chars.x);
	s((int[8]){0xe7, 0xe7, 0x7e, 0x3c, 0x3c, 0x7c, 0xe0, 0xe0}, &d->chars.y);
	s((int[8]){0xe7, 0xf7, 0xf7, 0xff, 0xff, 0xff, 0xef, 0xe7}, &d->chars.z);
	s((int[8]){0, 0, 0, 0, 0, 0, 0x18, 0x18}, &d->chars.dot);
	s((int[8]){0, 0, 0, 0, 0, 0, 0}, &d->chars.spc);
	s((int[8]){0, 0x18, 0x18, 0, 0, 0x18, 0x18, 0}, &d->chars.semi);
	s((int[8]){0x7e, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7e}, &d->chars.n0);
	s((int[8]){0x38, 0x78, 0xf8, 0x38, 0x38, 0x38, 0x38, 0x38}, &d->chars.n1);
	s((int[8]){0x7e, 0xff, 0xe7, 0x0e, 0x38, 0xe0, 0xff, 0xff}, &d->chars.n2);
	s((int[8]){0xfe, 0xff, 0x07, 0xfe, 0xfe, 0x07, 0xff, 0xfe}, &d->chars.n3);
	s((int[8]){0xee, 0xee, 0xee, 0xff, 0xff, 0x0e, 0x0e, 0x0e}, &d->chars.n4);
	s((int[8]){0xff, 0xff, 0xe0, 0xfe, 0xff, 0x07, 0xff, 0x7e}, &d->chars.n5);
	s((int[8]){0x7e, 0xff, 0xe0, 0xfe, 0xff, 0xe7, 0xff, 0x7e}, &d->chars.n6);
	s((int[8]){0xff, 0xff, 0x07, 0x0e, 0x1c, 0x38, 0x38, 0x38}, &d->chars.n7);
	s((int[8]){0x7e, 0xff, 0xe7, 0x7e, 0x7e, 0xe7, 0xff, 0x7e}, &d->chars.n8);
	s((int[8]){0x7e, 0xff, 0xe7, 0xff, 0x7f, 0x07, 0xff, 0x7e}, &d->chars.n9);
	s((int[8]){0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60}, &d->chars.slh);
	s((int[8]){0x66, 0x66, 0x0c, 0x0c, 0x18, 0x18, 0x33, 0x33}, &d->chars.prc);
	s((int[8]){0x18, 0x18, 0x18, 0x18, 0, 0x18}, &d->chars.exc);
}

void	init_font(t_ed *d)
{
	*d = (t_ed){.chars.a.bit = {0x7e, 0xff, 0xe7, 0xe7, 0xff, 0xff, 0xe7,
	0xe7},
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
	.chars.u.bit = {0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7e}};
	part_w(d);
}

void	draw_bitmap(t_ed *d, t_bitmap bitmap, t_font f)
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
				sdl_put_pix(&d->pixels, f.x + i, f.y + j, f.col);
			}
		}
	}
}

void	draw_char(t_ed *d, t_font f)
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
	else if (c == 'J')
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
	else if (c == 'U')
		draw_bitmap(d, d->chars.u, f);
	else if (c == 'V')
		draw_bitmap(d, d->chars.v, f);
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
	else if (c == '3')
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

void	draw_string(t_ed *d, t_font f)
{
	int			x_start;

	x_start = f.x;
	while (*f.str)
	{
		draw_char(d, f);
		f.x += 10;
		f.str++;
		if (*f.str == '\n' && ((f.x = x_start) == x_start) && f.str++)
			f.y += 36;
	}
}