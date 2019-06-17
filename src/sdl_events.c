#include "alt.h"

void    event_hooks(t_sdl *sdl, bool *end)
{
     if (sdl->event.type == SDL_QUIT)
            *end = true;
}
