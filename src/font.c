#include "../includes/doom_nukem.h"

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

void	handle_keypress(int *delay)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		else if (e.key.keysym.sym == SDLK_RETURN)
			*delay = 0;
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			*delay = 0;
	}
}
