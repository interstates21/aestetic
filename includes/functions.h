#include "alt.h"

void    sdl_init(t_sdl *sdl);
void    sdl_init_renderer(t_sdl *sdl);
void    sdl_clean(t_sdl *sdl);

void    sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);
void    sdl_clean(t_sdl *sdl);
void    event_hooks(t_sdl *sdl, bool *end);

t_rgb   new_rgb(int r, int g, int b);





void    print_err(const char *err);