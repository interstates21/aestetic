#include "../includes/editor.h"

Uint32 *get_screen_pixels(void)
{
    Uint32 *pixels;

    if (!(pixels = (Uint32 *)malloc(500 * 500 * sizeof(Uint32))))
        print_err("allocating pixels failed.");
    memset(pixels, 0, 500 * 500 * sizeof(Uint32));
    return (pixels);
}



void sdl_apply_renderer(t_sdl *sdl, t_ed *ed)
{
        SDL_RenderClear(sdl->renderer);
        SDL_UpdateTexture(sdl->texture, NULL, ed->pixels, 500 * sizeof(Uint32));
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
        SDL_RenderPresent(sdl->renderer);
        sdl_clear_texture(&(ed->pixels));
}


void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color)
{
     (*pixels)[x + (y * 500)] = color;
    
}
