#include "../includes/editor.h"

Uint32 *get_screen_pixels(void)
{
    Uint32 *pixels;

    if (!(pixels = (Uint32 *)malloc(ED_W * ED_H * sizeof(Uint32))))
        print_err("allocating pixels failed.");
    memset(pixels, 0, ED_W * ED_H * sizeof(Uint32));
    return (pixels);
}


void init_texure_picker_rect( SDL_Rect *SrcR, SDL_Rect *DestR)
{
    SrcR->x = 0;
    SrcR->y = 0;
    SrcR->w = SHAPE_SIZE;
    SrcR->h = SHAPE_SIZE;
    DestR->x = ED_W - 200 / 2 - SHAPE_SIZE / 2;
    DestR->y = ED_H - 200 / 2 - SHAPE_SIZE / 2;
    DestR->w = SHAPE_SIZE;
    DestR->h = SHAPE_SIZE;
}

void sdl_apply_renderer(t_sdl *sdl, t_ed *ed)
{
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *picker_tex;

    SDL_RenderClear(sdl->renderer);
    SDL_UpdateTexture(sdl->texture, NULL, ed->pixels, ED_W * sizeof(Uint32));
    SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
    if (ed->texture_picker) {
        picker_tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->texture_picker);
        init_texure_picker_rect(&SrcR, &DestR);
        SDL_RenderCopy(sdl->renderer, picker_tex, &SrcR, &DestR);
    }
    SDL_RenderPresent(sdl->renderer);
    sdl_clear_texture(&(ed->pixels));
}


void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color)
{
    if (x < 0 || y < 0 || x > ED_W - 1 || y > ED_H - 1)
        return;
     (*pixels)[x + (y * ED_W)] = color;
    
}
