#include "alt.h"

// todo: resize window

void       render(t_sdl *sdl)
{
    int x;

    x = 0;
    while(x < WIDTH)
    {
        sdl_put_pix(&(sdl->pixels), x, 1, 0x0000ff);
        sdl_put_pix(&(sdl->pixels), x, 2, 0x0000ff);
        sdl_put_pix(&(sdl->pixels), x, 3, 0x0000ff);
        sdl_put_pix(&(sdl->pixels), x, 4, 0x0000ff);
        sdl_put_pix(&(sdl->pixels), x, 5, 0x00ffff);
        x++;
    }
}

Uint32    *get_screen_pixels(void) {
    Uint32 *pixels;

    if (!(pixels = (Uint32*)malloc(WIDTH * HEIGHT * sizeof(Uint32)))) // todo: make sure we don't need 1 extra memory cell
        print_err("allocating pixels failed.");
    memset(pixels, 0, WIDTH * HEIGHT * sizeof(Uint32));
    return (pixels);
}


void    run(t_sdl *sdl, t_scene *scene)
{
    bool        end;

    print_map(scene);
    init_contols(scene);
    end = false;
    while (!end)
    {
        listen_controls();
        apply_controls(&(scene->player));
        render(sdl);
        SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(Uint32));
        SDL_RenderClear(sdl->renderer);
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
        SDL_RenderPresent(sdl->renderer);
        SDL_WaitEvent(&(sdl->event));
        if (sdl->event.type == SDL_QUIT)
            end = true;
    }
}

bool    validate_arg(char **argv)
{
    if (argv)
        return (true);
    return (true);
}

int     main(int argc, char **argv)
{
    t_sdl   sdl;
    t_scene scene;

    if (argc != 2)
        print_err("Usage: ./aestetic [mapname]");
    if (!validate_arg(argv))
        print_err("Wrong arg.");
    parse_manager(&scene, argv[1]);
    sdl_init(&sdl);
    sdl_init_renderer(&sdl);
    sdl.pixels = get_screen_pixels();
    run(&sdl, &scene);
    sdl_clean(&sdl); 
    return 0;
}