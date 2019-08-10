#include "alt.h"

void    sdl_init_renderer(t_sdl *sdl)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
    sdl->texture = SDL_CreateTexture(sdl->renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); // 32 bit image TODO: try 4 bit
}

void    sdl_init(t_sdl *sdl)
{
    SDL_Init(SDL_INIT_VIDEO);
    sdl->window = SDL_CreateWindow("Aestetic",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
}