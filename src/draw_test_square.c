#include "alt.h"

void draw_test_square(Uint32 **pixels, t_v2f v) {
    for(int i = 0; i <  20; i++) {
        for (int j = 0; j < 20; j++) {
             sdl_put_pix(pixels, (int)v.x + i, (int)v.y + j, 0x0000ff);
        }
    }
}

