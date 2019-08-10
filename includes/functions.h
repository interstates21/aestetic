#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "alt.h"

void    sdl_init(t_sdl *sdl);
void    sdl_init_renderer(t_sdl *sdl);
void    sdl_clean(t_sdl *sdl);

void    sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);
void    sdl_clean(t_sdl *sdl);

t_rgb   new_rgb(int r, int g, int b);

t_v2f   new_v2f(double x, double y);
t_v2    new_v2(int x, int y);

void	rotate_z(t_v2f *p, float teta);


void init_textures(t_scene *scene);
void    print_err(const char *err);


void	parse_manager(t_scene *scene, char *filename);
void    print_map(t_scene *scene);

void    init_contols(t_scene *scene);
void    apply_controls(t_player *player, char **map);
void    listen_controls(t_player *player, bool *end);

void    init_render(t_scene *scene);
void    render(t_scene *scene);
void    render_line(t_scene *scene, t_ray *ray, int x);
void    cast_ray(t_scene *scene, t_ray *ray, int x);

void	draw_test_square(t_scene *scene);
void     sdl_clear_texture(Uint32 **pixels);
void     print_v2(t_v2 v, char *s);
void     print_v2f(t_v2f v, char *s);
void test_controls(t_player *player, char **map);

#endif