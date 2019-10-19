#include "../includes/editor.h"

void render(t_ed *ed) {
     for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            sdl_put_pix(&(ed->pixels), i , j, 0xff0000);
        }
    }
}

void sdl_apply_renderer(t_sdl *sdl, t_ed *ed)
{
        SDL_UpdateTexture(sdl->texture, NULL, &(ed->pixels), 500 * sizeof(Uint32));
        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
        SDL_RenderPresent(sdl->renderer);
        sdl_clear_texture(&(ed->pixels));
        SDL_RenderClear(sdl->renderer);
}


void run(t_sdl *sdl, t_ed *ed)
{
    bool end;

        SDL_Event e;
    ed->pixels = get_screen_pixels();
    end = false;
    while (!end)
    {
        
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        // listen_controls(&end);
        render(ed);
        sdl_apply_renderer(sdl, ed);

    }
    SDL_Delay(2000);
    SDL_Quit();
}

int			main() {

    t_ed    ed;
    t_sdl   sdl;
    sdl_init(&sdl);
    sdl_init_renderer(&sdl);

    run(&sdl, &ed);

	return (0);
}
