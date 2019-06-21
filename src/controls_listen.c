#include "alt.h"

# define UP (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
# define DOWN (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
# define LEFT (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])
# define RIGHT (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])

void    listen_controls(t_player *player)
{
    const Uint8 *state;

    state =  SDL_GetKeyboardState(NULL);
    player->move_forw = UP ? true : false;
    player->move_back = DOWN ? true : false;
    player->rot_right = RIGHT ? true : false;
    player->rot_left = LEFT ? true : false;
    // printf("-%d-%d-%d-%d", player->move_forw, player->move_back, player->rot_right, player->rot_left);
}