#include "../includes/editor.h"

static void niceGrid(t_ed *ed) {
     for (int i = 0; i < ED_W; i++) {
        for (int j = 0; j < ED_H; j++) {
            if (j % GRID_GAP && i % GRID_GAP)  
                sdl_put_pix(&(ed->pixels), i , j, GRID_COL_1);
            else
                sdl_put_pix(&(ed->pixels), i , j, GRID_COL_2);
        }
    }
}


static void init_render(t_ed *ed) {
    ed->pixels = get_screen_pixels();
    ed->controller.mouse = new_v2(0, 0);
    ed->controller.mouse_is_pressed = false;
}


t_wall new_wall(int x1, int y1, int x2, int y2) {
    t_wall wall;

    wall.v1 = new_v2(x1, y1);
    wall.v2 = new_v2(x2, y2);
    wall.is_door = false;
    wall.is_portal = false;

    return (wall);
}

void render_sector(t_ed *ed) {
    const t_wall walls[3] = {
        new_wall(10, 10, 10, ed->controller.mouse.x),
        new_wall(10, 20, 15, ed->controller.mouse.x),
        new_wall(15, 30, 20, ed->controller.mouse.x),
    };

    int i = 0;
    while (i < 3) {
        line(walls[i].v1, walls[i].v2, ed, BLUE);
        i++;
    }
}

void render_map() {
    
}

void render_manager(t_sdl *sdl, t_ed *ed)
{
    bool end;

    init_render(ed);
    SDL_Event e;
    end = false;
    while (!end)
    {
        listen_controls(&end, ed);
        niceGrid(ed);
        // render_map(ed);
        render_sector(ed);
        sdl_apply_renderer(sdl, ed);

    }
    SDL_Delay(2000);
    SDL_Quit();
}