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


t_wall new_wall(int x1, int y1, int x2, int y2)
{
    t_wall wall;

    wall.v1 = new_v2(x1, y1);
    wall.v2 = new_v2(x2, y2);
    wall.is_door = 0;
    wall.is_portal = -1;
    return (wall);
}

void render_sector(t_ed *ed, t_sect *s)
{
    Uint32 color;
    int i = 0;
    while (i < s->n_walls)
    {
        if (ed->selection.selected_wall == &s->walls[i])
            color = RED;
        else if (s->walls[i].is_door)
			color = DOOR;
        else
            color = s->walls[i].is_portal > -1 ? MGN : BLUE;
        bold_line(s->walls[i].v1, s->walls[i].v2, ed, color);
        i++;
    }
}


void render_map(t_ed *ed)
{
	int 	i;

	i = -1;
	while (++i < ed->n_sect)
		render_sector(ed, &ed->seclist[i]);
	i = -1;
	while (++i < ed->n_walls)
		bold_line(ed->walls[i].v1, ed->walls[i].v2, ed, GRN);
}

void render_manager(t_sdl *sdl, t_ed *ed)
{
    bool end;
    int 	i;

    init_render(ed);
    SDL_Event e;
    end = false;
    
    while (!end)
    {
        listen_controls(&end, ed);
        niceGrid(ed);
		render_map(ed);
		draw_string(ed, (t_font){.str = "abcdefgxyz", .x = 100, .y = 100, .col = 0x111111});
        sdl_apply_renderer(sdl, ed);
    }
    SDL_Delay(2000);
    SDL_Quit();
}