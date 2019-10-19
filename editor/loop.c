#include "../includes/editor.h"

static void niceGrid(t_ed *ed) {
     for (int i = 0; i < ED_W; i++) {
        for (int j = 0; j < ED_H; j++) {
            if (j % 40 && i % 40)  
                sdl_put_pix(&(ed->pixels), i , j, 0xa4a4a4);
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
        niceGrid(ed);
        sdl_apply_renderer(sdl, ed);

    }
    SDL_Delay(2000);
    SDL_Quit();
}