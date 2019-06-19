#include "alt.h"

void            line(Uint32 **pixels, int x, int head, int foot)
{

    int b = MAX(head, foot);
    int a = MIN(head, foot);

    while (a < b)
    {
        sdl_put_pix(pixels, x, a, 0x0000ff);
        a++;
    }
}

void    render_line(t_scene *scene, int x, t_ray *ray)
{
    int line_height = (int)(HEIGHT / ray->dist_hit)
    int head = -line_height / 2 + HEIGHT / 2;
    int foot = line_height / 2 + HEIGHT / 2;

    head = CLAMP(head, 0, HEIGHT - 1);
    foot = CLAMP(foot, 0, HEIGHT - 1);


    Uint32 color = 0x0000ff;
    if (ray->hit_side == 'e')
        color /= 2;

    line(&(scene->pixels), x, head, foot, color);
}