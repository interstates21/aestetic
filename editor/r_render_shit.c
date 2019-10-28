#include "../includes/editor.h"

void draw_square(t_ed *ed, t_v2 c, int r, Uint32 col)
{
    int i;
    int j;

    i = -r;
    while (i < r) {
        j = -r;
        while (j < r) {
            sdl_put_pix(&(ed->pixels), c.x + j, c.y + i, col);
            j++;
        }
        i++;
    }
}

void nice_grid(t_ed *ed)
{
     for (int i = 0; i < ED_W; i++) {
        for (int j = 0; j < ED_H; j++) {
            if (j % GRID_GAP && i % GRID_GAP)  
                sdl_put_pix(&(ed->pixels), i , j, GRID_COL_1);
            else
                sdl_put_pix(&(ed->pixels), i , j, GRID_COL_2);
        }
    }
}
