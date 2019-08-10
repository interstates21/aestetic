#include "alt.h"
#define NARROW_EYE_EFFECT 2 // normal - 2

void            line(Uint32 **pixels, int x, int head, int foot, Uint32 color)
{

    int b = MAX(head, foot);  
    int a = MIN(head, foot);

    while (a < b)
    {
        sdl_put_pix(pixels, x, a, color);
        a++;
    }
}


// void            drawTexture() {
//         double wallX;
//     if (ray->hit_side == 'e')
//         wallX = posY + ray->dist_hit * ray.dir.y;
//       else
//         wallX = posX + ray->dist_hit * ray.dir.x;
//     wallX -= floor((wallX));

//     for(int y = drawStart; y<drawEnd; y++)
//       {
//         int d = y * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
//         // TODO: avoid the division to speed this up
//         int texY = ((d * texHeight) / lineHeight) / 256;
//         Uint32 color = texture[texNum][texHeight * texY + texX];
//         //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//         if(side == 1) color = (color >> 1) & 8355711;
//         buffer[y][x] = color;
//       }
//     }
// }
// Uint32  chooseColor() {

// }

void    render_line(t_scene *scene, t_ray *ray, int x)
{
    int line_height = (int)(HEIGHT / ray->dist_hit);
    int head = -line_height / NARROW_EYE_EFFECT + HEIGHT / 2;
    int foot = line_height / NARROW_EYE_EFFECT + HEIGHT / 2;



    head = CLAMP(head, 0, HEIGHT - 1);
    foot = CLAMP(foot, 0, HEIGHT - 1);


    Uint32 color = 0x0000ff;
    Uint32 foot_color = 0x000055;
    Uint32 head_color = 0x000022;
    if (ray->hit_side == 'e')
        color /= 2;

    line(&(scene->pixels), x, head, foot, color);
    line(&(scene->pixels), x, head, 0, head_color);
    line(&(scene->pixels), x, foot, HEIGHT, foot_color);
}