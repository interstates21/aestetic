#include "../includes/editor.h"

void render_sector_mosters(t_ed *ed)
{
    int i;

    if (!ed->n_mns)
        return ;
    i = 0;
    while (i < ed->n_mns)
    {
        draw_square(ed, ed->monst[i].pos, 5, 0xff0000);
        i++;
    } 
}

void render_sector_sprites(t_ed *ed)
{
    int i;

    if (!ed->n_sprt)
        return ;
    i = 0;
    while (i < ed->n_sprt)
    {
        draw_square(ed, ed->sprt[i].pos, 5, 0x22ffff);
        i++;
    }
}
