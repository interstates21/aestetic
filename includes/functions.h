#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "alt.h"

void    sdl_init(t_sdl *sdl);
void    sdl_init_renderer(t_sdl *sdl);
void    sdl_clean(t_sdl *sdl);

void    sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);

t_rgb   new_rgb(int r, int g, int b);

t_v2f   new_v2f(double x, double y);
t_v2    new_v2(int x, int y);

void	rotate_z(t_v2f *p, float teta);
double			x_prod(t_v2f a, t_v2f b);


// void init_textures(t_scene *scene);
void    print_err(const char *err);
void console_log_map(t_scene scene);

void init_controller(t_controller *controller);
// void	parse_manager(t_scene *scene, char *filename);
// void    print_map(t_scene *scene);

// void    apply_controls(t_player *player, char **map);
void	listen_controls(t_player *player, bool *end, t_controller *controller);
void	keyboard_input(t_player *player, bool *end, t_controller *controller);
void	mouse_aiming(t_player *player, t_controller *controller);
void    shitty_controller(t_controller *controller, bool *end, t_sdl sdl);
void paint_screen(t_scene *scene);
// void    init_render(t_scene *scene);
// void    render(t_scene *scene);
// void    render_line(t_scene *scene, t_ray *ray, int x);
// void    cast_ray(t_scene *scene, t_ray *ray, int x);

// void	draw_test_square(t_scene *scene);
void     sdl_clear_texture(Uint32 **pixels);
// void     print_v2(t_v2 v, char *s);
// void     print_v2f(t_v2f v, char *s);
// void test_controls(t_player *player, char **map);

int				init_vertices(char *str, t_v2f **arr, int *n_v);
int				player_init(t_scene *s, char *l);
int				fetch_int(char *str, int *i);
int				fetch_f(double *i, char *str, int *c);
t_sector		*sector_init(t_sector **arr, int *n_sectors, char *s, t_v2f *v);
int 			load_data(char *fname, t_scene *scene);
void            shitty_controller(t_controller *controller, bool *end, t_sdl sdl);
void            render(t_scene *scene);
void			draw_wall(t_draw *d, t_scene *s, int k);
int 			yaw(double y, double a, double w);
void			black_magic(t_math *m, t_scene *s);
void			render_wall(t_scene *s, t_draw *d, t_math m, int i);


#endif

