#include "editor.h"

bool	is_special_char(char c)
{
	return (c == 'y' || c == 'p' || c == 'q' || c == ',');
}

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
		y = is_special_char(*f->str) ? 2 * f->scale : 0;
		while (++i < CHAR_HEIGHT * f->scale)
			if (d->font[(int)c][j / f->scale] & (1 << i / f->scale))
				((uint32_t*)d->screen->pixels)[
					f->x + j + (f->y + i + y) * W] = f->color;
	}
}

void	draw_string(t_data *d, t_font f)
{
	if (f.scale <= 0)
		return ((void)printf("bad font scale\n"));
	while (*f.str)
	{
		draw_char(d, &f);
		f.x += (CHAR_WIDTH + 1) * f.scale;
		f.str++;
	}
}
