#include "../includes/editor.h"

static void render(t_ed *ed) {
     for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            sdl_put_pix(&(ed->pixels), i , j, 0xff0000);
        }
    }
}


void render_manager(t_sdl *sdl, t_ed *ed)
{
    bool end;

    SDL_Event e;
    ed->pixels = get_screen_pixels();
    end = false;
    while (!end)
    {
        listen_controls(&end);
        render(ed);
        sdl_apply_renderer(sdl, ed);

    }
    SDL_Delay(2000);
    SDL_Quit();
}