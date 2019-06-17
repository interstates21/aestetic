#include "alt.h"

void    init_contols(t_scene *scene)
{
    scene->player.pos = new_v2f(2, 2);
    scene->player.dir = new_v2f(-1, 0);
    scene->player.cam = new_v2f(0, 0.6);
	scene->player.move_speed = 0.1;
	scene->player.rot_speed = 0.1;
	scene->player.move_forw = 0;
	scene->player.move_back = 0;
	scene->player.rot_left = 0;
	scene->player.rot_right = 0;
}
