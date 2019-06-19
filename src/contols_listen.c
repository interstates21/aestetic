#include "alt.h"

# define UP (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_W])
# define DOWN (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_S])
# define LEFT (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_A])
# define RIGHT (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_D])

void    listen_controls(t_sdl *sdl)
{
    const Uint8 *state;

    state =  SDL_GetKeyboardState(NULL);
    sdl->player->move_forw = UP ? true : false
    sdl->player->move_back = DOWN ? true : false
    sdl->player->rot_right = RIGHT ? true : false
    sdl->player->rot_left = LEFT ? true : false
}