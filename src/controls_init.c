#include "alt.h"

void init_controller(t_controller *controller) {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    controller->move_forw = false;
    controller->move_back = false;
    controller->move_left = false;
    controller->move_right = false;
    controller->squat = false;
    controller->jumping = false;
    controller->rotating = false;
    controller->mouse = new_v2(0, 0);
}
