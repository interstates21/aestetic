#include "alt.h"

static void vline(t_scene *scene, int x, int y1, int y2, int top, int middle, int bottom)
{
    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    if (y2 == y1)
        pix(&(scene->pixels), x, y1, middle);
    else if (y2 > y1)
    {
        pix(&(scene->pixels), x, y1, top);
        for (int y = y1 + 1; y < y2; ++y)
            pix(&(scene->pixels), x, y, middle);
        pix(&(scene->pixels), x, y2, bottom);
    }
}
