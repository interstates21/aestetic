#include "alt.h"

void    init_contols(t_scene *scene)
{
	scene->player.move_speed = 0.1;
	scene->player.rot_speed = 2;
	scene->player.move_forw = 0;
	scene->player.move_back = 0;
	scene->player.rot_left = 0;
	scene->player.rot_right = 0;
}
