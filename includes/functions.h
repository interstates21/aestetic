#include "alt.h"

void    sdl_init(t_sdl *sdl);
void    sdl_init_renderer(t_sdl *sdl);
void    sdl_clean(t_sdl *sdl);

void    sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);
void    sdl_clean(t_sdl *sdl);
void    event_hooks(t_sdl *sdl, bool *end);

t_rgb   new_rgb(int r, int g, int b);

t_v2f   new_v2f(double x, double y);



void    print_err(const char *err);



void	parse_manager(t_scene *scene, char *filename);
void    print_map(t_scene *scene);

void    init_contols(t_scene *scene);
void    apply_controls(t_player *player);