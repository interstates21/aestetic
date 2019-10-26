#include "../includes/editor.h"

void draw_square(t_ed *ed, t_v2 c, int r, Uint32 col) {
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

void draw_mouse_highlight(t_ed *ed, t_v2 mouse) {
    int i;
    int j;
    int size;

    size = 8;
    i = -size;
    while (i < size) {
        j = -size;
        while (j < size) {
            sdl_put_pix(&(ed->pixels), mouse.x + j, mouse.y + i, 0xffff66);
            j++;
        }
        i++;
    }
}

void niceGrid(t_ed *ed) {
     for (int i = 0; i < ED_W; i++) {
        for (int j = 0; j < ED_H; j++) {
            if (j % GRID_GAP && i % GRID_GAP)  
                sdl_put_pix(&(ed->pixels), i , j, GRID_COL_1);
            else
                sdl_put_pix(&(ed->pixels), i , j, GRID_COL_2);
        }
    }
}

void draw_selection(t_ed *ed) {
    int offset;

    if (ed->selection.sprite == -1 && ed->selection.monster == -1)
        return ;
    draw_mouse_highlight(ed, ed->controller.mouse);
    if (ed->selection.sprite != -1) {
        offset = ed->selection.sprite * 36;
        circle(ed, new_v2(FIRST_SPRITE_W + offset, FIRST_SPRITE_H), 28, 0xff00ff);
    }
    if (ed->selection.monster == 0) {
        circle(ed, new_v2(MOSTER_1_PICKER_W, MOSTER_PICKER_H), 65, 0xff00ff);
    }
    else if (ed->selection.monster == 1) {
        circle(ed, new_v2(MOSTER_2_PICKER_W, MOSTER_PICKER_H), 65, 0xff00ff);
    }
}

