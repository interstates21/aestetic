#include "../includes/editor.h"


static void render_menu_field(t_ed *ed) {
     for (int i = ED_FIELD_W; i < ED_W; i++) {
        for (int j = 0; j < ED_FIELD_H; j++) {
            sdl_put_pix(&(ed->pixels), i , j, 0);
        }
    }
};

void render_menu(t_ed *ed) {
    
    render_menu_field(ed);
    draw_string(ed, 100, 100, new_text("Hello", 0xffff00, 2));
}