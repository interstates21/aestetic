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

bool       is_wall(t_v2 pos)
{
    return (map[pos.x] && map[pos.x][pos.y]);
}

void        cast_ray(t_scene *scene, t_ray *ray)
{
    ray->is_hit = false;

    while (!ray->is_hit)
    {
        /*  find absolute and delta dists to either x edge or y edge */
        if (ray->dist.x < ray->dist.y)
        {
            ray->dist.x += ray->dist_delta.x;
            ray->cell.x += ray->move_side.x;
            ray->side = 'e';
        }
        else
        {
            ray->dist.y += ray->dist_delta.y;
            ray->cell.y += ray->move_side.y;
            ray->side = 'w';
        }
        ray->is_hit = is_wall(ray->cell);
    }

    /* Either X or Y dist. Y in the world coordinate frame is X in a WallCell frame */
    ray->dist_hit = ray->side == 'e'
    ? (cell_x - scene->player->pos.x + (1 - ray->move_dir.x) / 2) / ray->dir.x
    : (cell_y - scene->player->pos.y + (1 - ray->move_dir.y) / 2) / ray->dir.y;

    render_line(scene, x, ray);
}
