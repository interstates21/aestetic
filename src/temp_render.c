#include "alt.h"

#define SQUARE_SIZE 25

void paint_screen(t_scene *scene)
{
    for (int i = 0; i < WIDTH; i++)
    {

        for (int j = 0; j < HEIGHT; j++)
        {
            pix(&(scene->pixels), i, j, 0xffffff);
        }
    }
}

void draw_test_square(t_scene *scene)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            pix(&(scene->pixels), i, j, 0x22222);
        }
    }
    for (int i = 0; i < SQUARE_SIZE; i++)
    {
        for (int j = 0; j < SQUARE_SIZE; j++)
        {
            pix(&(scene->pixels), (int)scene->player.pos.x + i, (int)scene->player.pos.y + j, 0x0000ff);
        }
    }
}