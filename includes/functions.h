#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "alt.h"

void sdl_init(t_sdl *sdl);
void sdl_init_renderer(t_sdl *sdl);
void sdl_clean(t_sdl *sdl);

void sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color);

t_rgb new_rgb(int r, int g, int b);

t_vt new_v2f(double x, double y);
t_v2i new_v2(int x, int y);

double		minf(double a, double b);
double		maxf(double a, double b);
int			mini(int a, int b);
int			maxi(int a, int b);
int			clampi(int i, int big, int low);

void rotate_z(t_vt *p, float teta);
double		line_eq(double k, double x, double b);
double		xprod(t_v2f a, t_v2f b);;

void controls_manager(t_scene *scene);
// void init_textures(t_scene *scene);
void print_err(const char *err);
void console_log_map(t_scene scene);

void init_controller(t_controller *controller);
// void	parse_manager(t_scene *scene, char *filename);
// void    print_map(t_scene *scene);

// void    apply_controls(t_player *player, char **map);
void listen_controls(t_player *player, bool *end, t_controller *controller);
void listen_controls(t_player *player, bool *end, t_controller *controller);
void apply_mouse_controls(t_player *player, t_controller *controller);
void aplly_controls(t_scene *scene, bool *end, t_sdl sdl);
void paint_screen(t_scene *scene);
// void    init_render(t_scene *scene);
// void    render(t_scene *scene);
// void    render_line(t_scene *scene, t_ray *ray, int x);
// void    cast_ray(t_scene *scene, t_ray *ray, int x);

// void	draw_test_square(t_scene *scene);
void sdl_clear_texture(Uint32 **pixels);
// void     print_v2(t_v2i v, char *s);
// void     print_v2f(t_vt v, char *s);
// void test_controls(t_player *player, char **map);
t_vt v_minus(t_vt a, t_vt b);
int init_vertices(char *str, t_vt **arr, int *n_v);
int player_init(t_scene *s, char *l);
int fetch_int(char *str, int *i);
int fetch_f(double *i, char *str, int *c);
t_sector *sector_init(t_sector **arr, int *n_sectors, char *s, t_vt *v);
int load_data(char *fname, t_scene *scene);
void render(t_scene *scene);
void init_draw(t_scene *scene, t_draw *d);
int	init_math(t_scene *scene, t_draw *d, t_math *m, int s);
void			transform(t_scene *scene, t_draw *d, t_math *m);
t_v2f			find_cross(t_v2f a, t_v2f b, t_cam c, int i);
int				init_cycle(t_scene *scene, t_draw *d);
void			draw_line(t_scene *s, t_scheme sc);
void print_screen(t_scene *scene);
void DrawScreen(t_scene *scene);
#endif
