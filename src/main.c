#include "../includes/alt.h"
#include "../includes/functions.h"

// todo: resize window



void sdl_apply_renderer(t_sdl sdl, Uint32 *pixels) {
        SDL_UpdateTexture(sdl.texture, NULL, pixels, WIDTH * sizeof(Uint32));
        SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
        SDL_RenderPresent(sdl.renderer);
        sdl_clear_texture(&pixels);
        SDL_RenderClear(sdl.renderer);
}

void run(t_scene scene, t_sdl sdl)
{
    bool            end;

    end = false;

    init_controller(&(scene.controller));
    // todo  init_textures(scene);
    while (!end)
    {
        // listen_controls(&(scene.player), &end, &(scene.controller));

        // t_player *player, t_controller *controller, bool *end, t_sdl sdl)
        listen_controls(&(scene.player), &end, &(scene.controller));
        /* mouse aiming */
        apply_mouse_controls(&(scene.player), &(scene.controller));
        controls_manager(&scene);
        render(&scene);
        sdl_apply_renderer(sdl, scene.pixels);
    }

    // todo clean_up();
    SDL_Quit();

}


bool validate_arg(char **argv)
{
    if (argv)
        return (true);
    return (true);
}

Uint32 *get_screen_pixels(void)
{
    Uint32 *pixels;

    if (!(pixels = (Uint32 *)malloc(WIDTH * HEIGHT * sizeof(Uint32))))
        print_err("allocating pixels failed.");
    memset(pixels, 0, WIDTH * HEIGHT * sizeof(Uint32));
    return (pixels);
}


void scene_init(t_scene *scene) {
	scene->sectors = NULL;
    scene->n_sectors = 0;
    scene->pixels = get_screen_pixels();
}


int main(int argc, char **argv)
{
    t_sdl sdl;
    t_scene scene;

    if (argc == 32)
        print_err("Usage: ./doom [mapname]");
    if (!validate_arg(argv))
        print_err("Wrong arg.");
    sdl_init(&sdl);
    scene_init(&scene);
    load_data("map-clear.txt", &scene);
    //console_log_map(scene);
    sdl_init_renderer(&sdl);
    run(scene, sdl);
    sdl_clean(&sdl);
    return 0;
}
