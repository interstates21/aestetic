#include "../includes/editor.h"

static void init_texure_picker_rect( SDL_Rect *SrcR, SDL_Rect *DestR, t_v2 pos, int size)
{
    SrcR->x = 0;
    SrcR->y = 0;
    SrcR->w = size;
    SrcR->h = size;
    DestR->x = ED_W - pos.x / 2 - size / 2;
    DestR->y = ED_H - pos.y / 2 - size / 2;
    DestR->w = size;
    DestR->h = size;
}

void render_picker(t_ed *ed, t_sdl *sdl) {
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *picker_tex;

     if (ed->texture_picker) {
        picker_tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->texture_picker);
        init_texure_picker_rect(&SrcR, &DestR, new_v2(200, 200), SHAPE_SIZE);
        SDL_RenderCopy(sdl->renderer, picker_tex, &SrcR, &DestR);
    }
}

void render_monsters(t_ed *ed, t_sdl *sdl) {
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *tex;

    tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->monster[0].acting[1][0]);
    init_texure_picker_rect(&SrcR, &DestR, new_v2(180, 500), 100);
    SDL_RenderCopy(sdl->renderer, tex, &SrcR, &DestR);
    tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->monster[1].acting[0][0]);
    init_texure_picker_rect(&SrcR, &DestR, new_v2(400, 500), 100);
    SDL_RenderCopy(sdl->renderer, tex, &SrcR, &DestR);
}

void render_sprites(t_ed *ed, t_sdl *sdl) {
    SDL_Rect    SrcR;
    SDL_Rect    DestR;
    SDL_Texture *tex;
    int         i;
    int         offset;

    i       = 0;
    offset  = 0;
    while (i < ed->n_sprites) {
        tex = SDL_CreateTextureFromSurface(sdl->renderer, ed->sprites[i].texture);
        init_texure_picker_rect(&SrcR, &DestR, new_v2(600 - offset, 700), 40);
        SDL_RenderCopy(sdl->renderer, tex, &SrcR, &DestR);
        i++;
        offset += 80;
    }

}