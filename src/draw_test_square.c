#include "alt.h"

#define SQUARE_SIZE 10
void draw_test_square(t_scene *scene) {
    for(int i = 0; i <  scene->map_height + SQUARE_SIZE; i++) {
        for (int j = 0; j < scene->map_width + SQUARE_SIZE; j++) {
             sdl_put_pix(&(scene->pixels), i, j, 0x22222);
        }
    }
    for(int i = 0; i <  SQUARE_SIZE; i++) {
        for (int j = 0; j < SQUARE_SIZE; j++) {
             sdl_put_pix(&(scene->pixels), (int)scene->player.pos.x + i, (int)scene->player.pos.y + j, 0x0000ff);
        }
    }
}

