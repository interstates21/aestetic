#include "alt.h"
#define NARROW_EYE_EFFECT 2 // normal - 2
#define NICE_BLUE 0x4444ff

void line(Uint32 **pixels, int x, int head, int foot, Uint32 color)
{

    int b = MAX(head, foot);
    int a = MIN(head, foot);

    while (a < b)
    {
        sdl_put_pix(pixels, x, a, color);
        a++;
    }
}

void drawTexture(t_scene *scene, t_ray *ray, int x, int head, int foot, int line_height)
{
    double wall_x;
    int tex_num = scene->map[ray->cell.x][ray->cell.y] - 1 - '0';
    double pos_x = scene->player.pos.x;
    double pos_y = scene->player.pos.y;

    int b = MAX(head, foot);
    int a = MIN(head, foot);

    if (ray->hit_side == 'e')
        wall_x = pos_y + ray->dist_hit * ray->dir.y;
    else
        wall_x = pos_x + ray->dist_hit * ray->dir.x;
    wall_x -= floor((wall_x));

    int tex_x = (int)(wall_x * (double)(scene->tex_width));
    if (ray->hit_side == 'e' && ray->dir.x > 0)
        tex_x = scene->tex_width - tex_x - 1;
    if (ray->hit_side == 'w' && ray->dir.x < 0)
        tex_x = scene->tex_width - tex_x - 1;
    while (a < b)
    {
        int d = a * 256 - HEIGHT * 128 + line_height * 128;
        int tex_y = ((d * scene->tex_height) / line_height) / 256;
        // printf(" --- %d --- %d---%d-\n", tex_y, a, tex_num);
        Uint32 color = scene->textures[tex_num][scene->tex_width * tex_y + tex_x];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if (ray->hit_side == 'e')
            color = (color >> 1) & 8355711;
        sdl_put_pix(&(scene->pixels), x, a, color);
        a++;
    }
}

void render_line(t_scene *scene, t_ray *ray, int x)
{
    int line_height = (int)(NARROW_EYE_EFFECT * HEIGHT / ray->dist_hit);
    int head = -line_height / 2 + HEIGHT / 2;
    int foot = line_height / 2 + HEIGHT / 2;

    head = CLAMP(head, 0, HEIGHT - 1);
    foot = CLAMP(foot, 0, HEIGHT - 1);

    Uint32 color = 0x0000ff;
    Uint32 foot_color = 0x000055;
    Uint32 head_color = 0x000022;
    if (ray->hit_side == 'e')
        color /= 2;

    // line(&(scene->pixels), x,? head, foot, color);
    drawTexture(scene, ray, x, head, foot, line_height);
    line(&(scene->pixels), x, head, 0, head_color);
    line(&(scene->pixels), x, foot, HEIGHT, foot_color);
}