#include "alt.h"

void sdl_clean(t_sdl *sdl)
{
    // todo: delete[] pixels;
    SDL_DestroyTexture(sdl->texture);
    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->window);
    SDL_Quit();
}

void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color)
{
    if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
        return;
    (*pixels)[y * WIDTH + x] = color;
}

void sdl_clear_texture(Uint32 **pixels)
{
    ft_bzero(*pixels, WIDTH * HEIGHT * 4);
}