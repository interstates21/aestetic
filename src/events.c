#include "../includes/doom_nukem.h"

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	int			i;
	t_assets	*asset;

	if (event.keysym.sym == SDLK_ESCAPE)
		proper_exit(d);
	if (event.keysym.sym == SDLK_e)
	{
		i = -1;
		while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
		{
			asset = &d->assets[d->cursectnum][i];
			if (v2_len(v2_min(v3_to_v2(d->cam.pos), asset->world_pos)) <
				1.5 && !asset->used &&
				(asset->is_interactive || asset->is_autopick ||
				 asset->is_key || asset->is_jetpack))
			{
				use_asset(d, asset);
				return ;
			}
		}
		activate_door(d, &d->sectors[d->cursectnum]);
	}
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
}

void	proper_exit(t_data *d)
{
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

