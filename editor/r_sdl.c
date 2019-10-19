#include "../includes/editor.h"

Uint32 *get_screen_pixels(void)
{
    Uint32 *pixels;

    if (!(pixels = (Uint32 *)malloc(500 * 500 * sizeof(Uint32))))
        print_err("allocating pixels failed.");
    memset(pixels, 0, 500 * 500 * sizeof(Uint32));
    return (pixels);
}


void    sdl_init_renderer(t_sdl *sdl)
{
    // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
    sdl->texture = SDL_CreateTexture(sdl->renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);
}


void sdl_clean(t_sdl *sdl)
{
    // todo: delete[] pixels;
    SDL_DestroyTexture(sdl->texture);
    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->win);
    SDL_Quit();
}

void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color)
{
     (*pixels)[x + (y * 500)] = color;
    
}


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
	sdl->win = SDL_CreateWindow("doom_nukem editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);
	sdl->screen = SDL_GetWindowSurface(sdl->win);
}