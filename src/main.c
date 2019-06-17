#include "alt.h"

// todo: resize window

Uint32    *get_screen_pixels(void) {
    Uint32 *pixels;

    if (!(pixels = (Uint32*)malloc(WIDTH * HEIGHT * sizeof(Uint32)))) // todo: make sure we don't need 1 extra memory cell
        print_err("allocating pixels failed.");
    memset(pixels, 0, WIDTH * HEIGHT * sizeof(Uint32));
    return (pixels);
}

void    run(t_sdl *sdl)
{
    bool        end;

    end = false;
    while (!end)
    {
        SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(Uint32));
        SDL_RenderClear(sdl->renderer);
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
        SDL_RenderPresent(sdl->renderer);
        SDL_WaitEvent(&(sdl->event));
        event_hooks(sdl, &end);
    }
}

bool    validate_arg(char **argv)
{
    if (argv)
        return (true);
    return (false);
}

bool    parse_map(void)
{
    return (true);
}

int     main(int argc, char **argv)
{
    t_sdl   sdl;

    if (argc != 2)
        print_err("Usage: ./aestetic [mapname]");
    if (!validate_arg(argv))
        print_err("Wrong arg.");
    if (!parse_map())
        print_err("Parse failed.");
    sdl_init(&sdl);
    sdl_init_renderer(&sdl);
    sdl.pixels = get_screen_pixels();
    run(&sdl);
    sdl_clean(&sdl); 
    return 0;
}