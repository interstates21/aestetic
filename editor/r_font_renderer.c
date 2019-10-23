#include "../includes/editor.h"

void	draw_string(t_ed *ed, int x, int y, t_text text)
{
	int			x_start;

	x_start = x;
	while (*text.message)
	{
		draw_char(ed, text, new_v2(x, y));
		x += 10;
		text.message++;
		if (*text.message == '\n' && ((x = x_start) == x_start) && text.message++)
			y += (CHAR_HEIGHT + 10) * text.scale;
	}
}
