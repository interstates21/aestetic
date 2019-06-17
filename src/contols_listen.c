#include "alt.h"

void    event_hooks(t_sdl *sdl, bool *end)
{
     if (sdl->event.type == SDL_LEFT)
            *end = true;
}


// int				key_listener(int keycode, t_world *e)
// {
// 	if (keycode == 53)
// 		exit(1);
// 	if (keycode == K_TAB)
// 		e->color_mode = (e->color_mode + 1) % 2;
// 	if (keycode == K_UP)
// 		e->move_forw = (e->move_forw + 1) % 2;
// 	if (keycode == K_DOWN)
// 		e->move_back = (e->move_back + 1) % 2;
// 	if (keycode == K_RIGHT)
// 		e->rot_right = (e->rot_right + 1) % 2;
// 	if (keycode == K_LEFT)
// 		e->rot_left = (e->rot_left + 1) % 2;
// 	return (0);
// }