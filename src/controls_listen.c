#include "alt.h"

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
                 if (e.key.keysym.sym == SDLK_ESCAPE) {
                     *end = true;
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
