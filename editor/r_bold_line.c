#include "../includes/editor.h"

void bold_line(t_v2 p1, t_v2 p2, t_ed *ed, Uint32 color) {
    int stepDiff;
    int x;
    int y;
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);

    int stepX = p2.x >= p1.x ? 1 : -1;
    int stepY = p2.y >= p1.y ? 1 : -1;

    if (dx > dy) {
        stepDiff = (dy << 1) - dx;

        x = p1.x + stepX;
        y = p1.y;

        int i = 1;
        sdl_put_pix(&(ed->pixels), x, y, color);
        sdl_put_pix(&(ed->pixels), x + 1, y + 1, color);
        sdl_put_pix(&(ed->pixels), x - 1, y - 1, color);

        while (i <= dx) {
            if (stepDiff > 0) {
                stepDiff += (dy - dx) << 1;
                y += stepY;
            }
            else {
                stepDiff += dy << 1;
            }

            sdl_put_pix(&(ed->pixels), x, y, color);
            sdl_put_pix(&(ed->pixels), x + 1, y + 1, color);
            sdl_put_pix(&(ed->pixels), x - 1, y - 1, color);
             i++;
             x += stepX;
        }
    }

    else if (dx <= dy) {
        stepDiff = (dx << 1) - dy;
        x = p1.x;
        y = p1.y + stepY;
        int i = 1;

        sdl_put_pix(&(ed->pixels), x, y, color);

        while (i <= dy) {
            if (stepDiff > 0) {
                stepDiff += (dx - dy) << 1;
                x += stepX;
            }
            else
                stepDiff += dx << 1;
            sdl_put_pix(&(ed->pixels), x, y, color);
            sdl_put_pix(&(ed->pixels), x + 1, y + 1, color);
            sdl_put_pix(&(ed->pixels), x - 1, y - 1, color);
            i++;
            y += stepY;
        }

    } 
}