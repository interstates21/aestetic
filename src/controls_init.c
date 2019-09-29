#include "alt.h"

void init_controller(t_controller *controller) {
    controller->move_forw = false;
    controller->move_back = false;
    controller->rot_left = false;
    controller->rot_right = false;
    controller->falling = true;
    controller->ground = false;
    controller->moving = false;
    controller->ducking = false;
    controller->yaw = 0;
}