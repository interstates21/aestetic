#include "alt.h"

// todo: resize window


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
    init_render(scene);
    init_contols(scene);
    end = false;
    while (!end)
    {
        listen_controls();
        apply_controls(&(scene->player));
        render(sdl);
        /* Fill our ScreenTexture with the Pixels we have put */
        /* Texture are used for performance */
        SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(Uint32));
          /* Clear Window */
        SDL_RenderClear(sdl->renderer);
          /* Put Image(Texture) to Window */
          /* TODO: clear texture */
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
          /* Render Frame */
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