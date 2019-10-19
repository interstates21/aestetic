#include "../includes/editor.h"

void sdl_print_pix(Uint32 **pixels, int x, int y)
{
     ft_putnbr((*pixels)[x + (y * 500)]);
     ft_putchar('\n');
    
}

void sdl_clear_texture(Uint32 **pixels)
{
    ft_bzero(*pixels, 500 * 500 * 4);
}

void	sdl_init(t_sdl *sdl)
{
    SDL_Init(SDL_INIT_VIDEO);
	if (!(sdl->win = SDL_CreateWindow("doom_nukem editor", 0,0, 500, 500, 0)))
		print_err(SDL_GetError());

}

void    sdl_init_renderer(t_sdl *sdl)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
    if (!sdl->renderer)
       	print_err(SDL_GetError());
    sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);
    if (!sdl->texture)
       	print_err(SDL_GetError());

}

void sdl_clean(t_sdl *sdl)
{
    // todo: delete[] pixels;
    SDL_DestroyTexture(sdl->texture);
    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->win);
    SDL_Quit();
}