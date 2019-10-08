#include "../includes/doom_nukem.h"

void	draw_char(t_data *d, t_font *f)
{
	int		i;
	int		j;
	char	c;
	int		y;

	c = *f->str & 0x7F;
	if (c < ' ')
		c = 0;
	else
		c -= ' ';
	j = -1;
	while (++j < CHAR_WIDTH * f->scale)
	{
		i = -1;
		y = SPECIAL_CHAR(*f->str) ? 2 * f->scale : 0;
		while (++i < CHAR_HEIGHT * f->scale)
			if (d->font[(int)c][j / f->scale] & (1 << i / f->scale))
			{
				putpixel(d, f->x + j, f->y + i + y, f->color);
				putpixel(d, f->x + j, f->y + i + y + f->scale, 0x000000);
			}
	}
}

void	draw_string(t_data *d, t_font f)
{
	int			x_start;

	if (f.scale <= 0)
		return ((void)printf("bad fond scale\n"));
	x_start = f.x;
	while (*f.str)
	{
		draw_char(d, &f);
		f.x += (CHAR_WIDTH + 1) * f.scale;
		f.str++;
		if (*f.str == '\n' && ((f.x = x_start) == x_start) && f.str++)
			f.y += (CHAR_HEIGHT + 10) * f.scale;
	}
}
