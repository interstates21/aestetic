#include "../includes/editor.h"



void render_texture_picker(t_ed *ed) {
	int		i;
	int		j;
	t_v2	pos;

	i = 0;
	pos = new_v2(ED_W - 150, ED_H - 150);
	while (i < PICKER_SIZE)
	{
		j = 0;
		while (j < PICKER_SIZE)
		{
			j++;
			 sdl_put_pix(&(ed->pixels), pos.x + i , pos.y + j, 0);
		}
		i++;
	}
}