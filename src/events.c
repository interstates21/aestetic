#include "../includes/doom_nukem.h"

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE && !event.repeat)
		pause_menu(d);
	else if (event.keysym.sym == SDLK_p)
		pause_menu(d);
	else if (event.keysym.sym == SDLK_PAUSE)
		d->debug_pause = true;
	else if (event.keysym.sym == SDLK_e)
		press_e(d);
}

void	event_mouse_motion(t_data *d, SDL_MouseMotionEvent event)
{
	if (SDL_GetRelativeMouseMode() == SDL_FALSE)
		return ;
	d->cam.y_offset += event.yrel * MOUSE_SENSITIVTY * 0.5;
	d->cam.y_offset = CLAMP(d->cam.y_offset, -MAX_Y_OFFSET, MAX_Y_OFFSET);
	d->cam.rot += event.xrel * MOUSE_SENSITIVTY * 0.001;
}

void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event)
{
	(void)d;
	if (event.button == SDL_BUTTON_LEFT)
		d->left_mouse_button = event.state == SDL_PRESSED ?
			MOUSE_PRESSED : MOUSE_RELEASED;
	if (event.button == SDL_BUTTON_RIGHT)
		d->right_mouse_button = event.state == SDL_PRESSED ?
			MOUSE_PRESSED : MOUSE_RELEASED;
	if (event.state == SDL_RELEASED)
	{
	}
}

void	proper_exit(t_data *d)
{
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	err_exit(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
