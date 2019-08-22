#include "alt.h"

// todo: resize window

// SDL_Texture   *load_sur(SDL_Renderer *ren) {
//     SDL_Texture *tex = NULL;

//     SDL_Surface *sur = SDL_LoadBMP("src/0.bmp");
//     if (sur == NULL) {
//         ft_putstr(SDL_GetError());
//         exit(1);
//     }

//      tex = SDL_CreateTextureFromSurface(ren, sur);

//      SDL_FreeSurface(sur);

//      return (tex);
// }

bool validate_arg(char **argv)
{
    if (argv)
        return (true);
    return (true);
}

Uint32 *get_screen_pixels(void)
{
    Uint32 *pixels;

    if (!(pixels = (Uint32 *)malloc(WIDTH * HEIGHT * sizeof(Uint32)))) // todo: make sure we don't need 1 extra memory cell
        print_err("allocating pixels failed.");
    memset(pixels, 0, WIDTH * HEIGHT * sizeof(Uint32));
    return (pixels);
}

void run(t_sdl *sdl, t_scene *scene)
{
    bool end;

    init_render(scene);
    init_contols(scene);
    init_textures(scene);
    end = false;
    /* todo: proper timing */
    while (!end)
    {
        listen_controls(&(scene->player), &end);
        apply_controls(&(scene->player), scene->map);
        render(scene);
        draw_test_square(scene);
        SDL_UpdateTexture(sdl->texture, NULL, scene->pixels, WIDTH * sizeof(Uint32));
        // SDL_Texture *tex = load_sur(sdl->renderer);
        // SDL_RenderCopy(sdl->renderer, tex, NULL, NULL);
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
        SDL_RenderPresent(sdl->renderer);
        sdl_clear_texture(&(scene->pixels));
        SDL_RenderClear(sdl->renderer);
    }
}
int main(int argc, char **argv)
{
    t_sdl sdl;
    t_scene scene;

    if (argc != 2)
        print_err("Usage: ./doom [mapname]");
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