#include "alt.h"

void	apply_mouse_controls(t_player *player, t_controller *controller)
{
	SDL_GetRelativeMouseState(&controller->mouse.x, &controller->mouse.y);
	if (SDL_GetRelativeMouseMode())
	{
		player->angle += controller->mouse.x * 0.007f;
		controller->yaw = clamp(controller->yaw - controller->mouse.y * (-0.025f), -5, 5);
		player->yaw = controller->yaw - player->dir.z * 0.5f;
	}
}
