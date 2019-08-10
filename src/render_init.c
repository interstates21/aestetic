#include "alt.h"

void    init_render(t_scene *scene)
{
    scene->player.view = new_v2f(0, 1);
    scene->player.pos = new_v2f(6, 5);
    scene->player.dir = new_v2f(-1, 0);
}