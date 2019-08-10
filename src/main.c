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
        listen_controls(&(scene->player), &end);
        apply_controls(&(scene->player), scene->map);
        render(scene);
        draw_test_square(&scene->pixels, scene->player.pos);
        SDL_UpdateTexture(sdl->texture, NULL, scene->pixels, WIDTH * sizeof(Uint32));
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
        SDL_RenderPresent(sdl->renderer);
        sdl_clear_texture(&(scene->pixels));
        SDL_RenderClear(sdl->renderer);
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
    scene.pixels = get_screen_pixels();
    run(&sdl, &scene);
    sdl_clean(&sdl); 
    return 0;
}