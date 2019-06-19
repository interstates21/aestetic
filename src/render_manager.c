#include "alt.h"

/*
ray:
    t_v2f	dir;
	t_v2	move_side;
	t_v2    cell;
    t_v2f   dist;
    t_v2f   dist_delta;
    char    hit_side;
    bool    is_hit;
    double  dist_hit;
*/

void       render(t_sdl *sdl, t_scene *scene)
{
    /* todo: create threads */

    double  cam_space;
    t_ray   ray;
    int     i;

    i = 0;
    while (i < WIDTH)
    {
        /* Map x from Screen Space to Cam Space of size. 2*/
        cam_space = 2 * x / (double)WIDTH - 1;
        /* Create a Coordinate Frame for player and apply FieldOfView to camera. */
        ray.dir.x = scene->player->dir.x + scene->player->view.x * cam_space; 
        ray.dir.y = scene->player->dir.y + scene->player->view.y * cam_space;
        /* Coordinates of a current map cell. */
        ray.cell = new_v2((int)scene->player.pos.x, (int)scene->player.pos.y);
        /* In order to check cell.isEmpty we must check each single position which is slow to death.
        However we may use geometry (DDA algorithm) to check a value only on a Cell edge. */
        /* Shortcut for Pythagorus */
        ray.dist_delta = new_v2f(abs(1 / ray.dir.x), abs(1 / ray.dir.y));
        ray.move_side.x = ray.dir.x > 0 ? 1 : -1;
        ray.move_side.y = ray.dir.y > 0 ? 1 : -1;
        /* Init an initial dist to the nearest cell edge */
        ray.dist.x = ray.dir.x < 0
        ? (scene->player.pos.x - cell_x) * dist_delta.x
        : (cell_x + 1.0 - scene->player.pos.x) * dist_delta.x;
        ray.dist.y = ray.dir.y < 0
        ? (scene->player.pos.y - cell_y) * dist_delta.y
        : (cell_y + 1.0 - scene->player.pos.y) * dist_delta.y;
        cast_ray(scene, &ray);
        i++;
    }
}