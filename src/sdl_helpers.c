#include "alt.h"

void    sdl_clean(t_sdl *sdl)
{
    // todo: delete[] pixels;
    SDL_DestroyTexture(sdl->texture);
    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->window);
    SDL_Quit();
}

void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color)
{
    (*pixels)[y * WIDTH + x] = color;
}
