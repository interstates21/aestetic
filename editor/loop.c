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
    ed->selection.selected_wall = NULL;
    ed->selection.selected_vertex = NULL;
}


t_wall new_wall(int x1, int y1, int x2, int y2) {
    t_wall wall;

    wall.v1 = new_v2(x1, y1);
    wall.v2 = new_v2(x2, y2);
    wall.is_door = false;
    wall.is_portal = false;

    return (wall);
}

void render_sector(t_ed *ed, t_wall *walls) {
    Uint32 color;
    int i = 0;
    while (i < 4) {
        if (ed->selection.selected_wall == &walls[i])
            color = RED;
        else
            color = BLUE;
        bold_line(walls[i].v1, walls[i].v2, ed, color);
        i++;
    }
}




void render_manager(t_sdl *sdl, t_ed *ed)
{
    bool end;

    init_render(ed);
    SDL_Event e;
    end = false;

    t_wall walls[4] = {
        new_wall(100, 100, 200, 100),
        new_wall(200, 100, 200, 200),
        new_wall(200, 200, 100, 200),
        new_wall(100, 200, 100, 100),
    };

    ed->initial_walls = walls;
    while (!end)
    {
        listen_controls(&end, ed);
        niceGrid(ed);
        // render_map(ed);
        render_sector(ed, walls);
        sdl_apply_renderer(sdl, ed);

    }
    SDL_Delay(2000);
    SDL_Quit();
}