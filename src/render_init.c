#include "alt.h"

void    init_render(t_scene *scene)
{
    scene->player.view = new_v2f(0, 0.6);
    scene->player.pos = new_v2f(2, 2);
    scene->player.dir = new_v2f(-1, 0);
}