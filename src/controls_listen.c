#include "alt.h"

# define UP (state[SDLK_w] == 1)
# define DOWN (state[SDLK_s] == 1)
# define LEFT (state[SDLK_a] == 1)
# define RIGHT (state[SDLK_d] == 1)

void    listen_controls(t_player *player, bool *end)
{

      SDL_Event e;

    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        *end = true;
    }
     if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP) {
                    player->move_forw = true;
                }
                if (e.key.keysym.sym == SDLK_DOWN) {
                     player->move_back = true;
                }
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    player->rot_right= true;
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                     player->rot_left = true;
                }
            }

     if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_UP) {
                    player->move_forw = false;
                }
                if (e.key.keysym.sym == SDLK_DOWN) {
                     player->move_back = false;
                }
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    player->rot_right= false;
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                     player->rot_left = false;
                }       
     }

}
