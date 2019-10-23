#include "../includes/editor.h"

void	draw_char(t_ed *ed, t_text text, t_v2 v)
{
	char c;
	
	c = ft_toupper(*(text.message));
	if (c == 'A')
		draw_bitmap(ed, text.chars.a, v, text.color);
	else if (c == 'B')
		draw_bitmap(ed, text.chars.b, v, text.color);
	else if (c == 'C')
		draw_bitmap(ed, text.chars.c, v, text.color);
	else if (c == 'D')
		draw_bitmap(ed, text.chars.d, v, text.color);
	else if (c == 'E')
		draw_bitmap(ed, text.chars.e, v, text.color);
	else if (c == 'F')
		draw_bitmap(ed, text.chars.f, v, text.color);
	else if (c == 'G')
		draw_bitmap(ed, text.chars.g, v, text.color);
	else if (c == 'H')
		draw_bitmap(ed, text.chars.h, v, text.color);
	else if (c == 'I')
		draw_bitmap(ed, text.chars.i, v, text.color);
	else if (c == 'J')
		draw_bitmap(ed, text.chars.j, v, text.color);
	else if (c == 'K')
		draw_bitmap(ed, text.chars.k, v, text.color);
	else if (c == 'L')
		draw_bitmap(ed, text.chars.l, v, text.color);
	else if (c == 'M')
		draw_bitmap(ed, text.chars.m, v, text.color);
	else if (c == 'N')
		draw_bitmap(ed, text.chars.n, v, text.color);
	else if (c == 'O')
		draw_bitmap(ed, text.chars.o, v, text.color);
	else if (c == 'P')
		draw_bitmap(ed, text.chars.p, v, text.color);
	else if (c == 'Q')
		draw_bitmap(ed, text.chars.q, v, text.color);
	else if (c == 'R')
		draw_bitmap(ed, text.chars.r, v, text.color);
	else if (c == 'S')
		draw_bitmap(ed, text.chars.s, v, text.color);
	else if (c == 'T')
		draw_bitmap(ed, text.chars.t, v, text.color);
	else if (c == 'U')
		draw_bitmap(ed, text.chars.u, v, text.color);
	else if (c == 'V')
		draw_bitmap(ed, text.chars.v, v, text.color);
	else if (c == 'W')
		draw_bitmap(ed, text.chars.w, v, text.color);
	else if (c == 'X')
		draw_bitmap(ed, text.chars.x, v, text.color);
	else if (c == 'Y')
		draw_bitmap(ed, text.chars.y, v, text.color);
	else if (c == 'Z')
		draw_bitmap(ed, text.chars.z, v, text.color);
	else if (c == '.')
		draw_bitmap(ed, text.chars.dot, v, text.color);
	else if (c == '!')
		draw_bitmap(ed, text.chars.exc, v, text.color);
	else if (c == '0')
		draw_bitmap(ed, text.chars.n0, v, text.color);
	else if (c == '1')
		draw_bitmap(ed, text.chars.n1, v, text.color);
	else if (c == '2')
		draw_bitmap(ed, text.chars.n2, v, text.color);
	else if (c == '3')
		draw_bitmap(ed, text.chars.n3, v, text.color);
	else if (c == '4')
		draw_bitmap(ed, text.chars.n4, v, text.color);
	else if (c == '5')
		draw_bitmap(ed, text.chars.n5, v, text.color);
	else if (c == '6')
		draw_bitmap(ed, text.chars.n6, v, text.color);
	else if (c == '7')
		draw_bitmap(ed, text.chars.n7, v, text.color);
	else if (c == '8')
		draw_bitmap(ed, text.chars.n8, v, text.color);
	else if (c == '9')
		draw_bitmap(ed, text.chars.n9, v, text.color);
	else if (c == ':')
		draw_bitmap(ed, text.chars.semi, v, text.color);
	else if (c == '/')
		draw_bitmap(ed, text.chars.slh, v, text.color);
	else if (c == '%')
		draw_bitmap(ed, text.chars.prc, v, text.color);
	else
		draw_bitmap(ed, text.chars.spc, v, text.color);
}
