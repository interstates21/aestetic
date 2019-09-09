#include "alt.h"

void printBigPoint(t_scene *scene, t_v2 const p)
{
    for (int i = p.x - 5; i < p.x + 5; i++)
        for (int j = p.y - 5; j < p.y + 5; j++)
            pix(&(scene->pixels), i, j, NICE_PURPLE);
}
void demoProjection(t_scene *scene)
{
    t_v2 p1 = new_v2(0, 0);
    t_v2 p2 = new_v2(100, 400);

    t_v2 const playerPos = new_v2(scene->player.pos.x, scene->player.pos.y);

    t_v2 np = new_v2(100, 200);
    t_v2 mp = new_v2(WIDTH / 3, HEIGHT / 3);

    line(np, mp, scene, NICE_BLUE);
    printBigPoint(scene, np);
}

void render(t_scene *scene)
{
    demoProjection(scene);
}