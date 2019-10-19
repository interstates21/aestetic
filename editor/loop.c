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
        console.log("hello");
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